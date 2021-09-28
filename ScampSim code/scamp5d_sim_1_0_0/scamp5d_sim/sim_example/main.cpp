/*************************************************************************
 * WEN FAN Dissertation Program
 *
 *************************************************************************/
 /*
  * Example 24 - Flooding and Bounding Box and Around Area De-active and Send Message to Interface
  *
  */

#include <scamp5.hpp>
#include <cmath>

using namespace SCAMP5_PE;


#define DEFAULT_FRAMERATE	60

// Global Variables
volatile int readout_mode;
volatile int threshold;
volatile int P_filter;

int main() {

	// Initialization
	vs_init();


	// Setup Host GUI

	auto display_1 = vs_gui_add_display("capture", 0, 0);
	auto display_2 = vs_gui_add_display("threshold", 0, 1);
	auto display_3 = vs_gui_add_display("filter", 0, 2);
	//auto display_4 = vs_gui_add_display("boundingbox", 1, 0);



	vs_gui_add_slider_latched("readout: ", 0, 4, 4, &readout_mode);
	vs_gui_add_slider("threshold: ", -120, 120, 10, &threshold);
	vs_gui_add_slider("noise filter radius: ", 0, 10, 1, &P_filter);

	vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);


	// Setup callback functions

	vs_on_host_connect([&]() {
		vs_led_on(VS_LED_2);
		// change frame rate slider on host GUI to our default value
		vs_gui_move_slider(VS_GUI_FRAME_RATE, DEFAULT_FRAMERATE);
	});

	vs_on_host_disconnect([&]() {
		vs_led_off(VS_LED_2);
		vs_enable_frame_trigger();
		vs_frame_trigger_set(1, DEFAULT_FRAMERATE);
	});


	// Setup Frame-rate

	vs_frame_trigger_set(1, DEFAULT_FRAMERATE);

	// Frame Loop
	while (1) {
		// sync with frame trigger timing and process interaction with host
		vs_frame_loop_control();

		// input a global value to a AREG for using as threshold
		scamp5_in(E, threshold);

		scamp5_kernel_begin();
		get_image(C, D);
		sub(A, C, E);// A = C - E
		where(A);// where A > 0
		MOV(R5, FLAG);
		all();

		//noise filting
		mov(B, A);
		mov(C, A);
		mov(D, A);
		mov(E, A);

		scamp5_shift(B, P_filter, 0);//move B to east with P_filter step
		where(B);// where B > 0
		MOV(R6, FLAG);// move B to R9
		all();

		scamp5_shift(C, -P_filter, 0);//move C to west with P_filter step
		where(C);// where C > 0
		MOV(R7, FLAG);// move C to R7
		all();

		scamp5_shift(D, 0, P_filter);//move D to north with P_filter step
		where(D);// where D > 0
		MOV(R8, FLAG);// move D to R8
		all();

		scamp5_shift(E, 0, -P_filter);//move E to south with P_filter step
		where(E);// where E > 0
		MOV(R9, FLAG);// move E to R9
		all();

		OR(R1, R6, R7);//R1=R6 and R7
		OR(R2, R8, R9);//R2=R8 and R9
		OR(R10, R1, R2);//R10=R11 and R12

		CLR(R1, R2, R6);
		CLR(R7, R8, R9);

		scamp5_kernel_end();

		// Upper Area de-active
		scamp5_kernel_begin();
		CLR(R11);
		scamp5_load_rect(R11, 0, 0, 2, 255);//draw a rectangle in R11
		OR(R9, R10, R11);
		MOV(R10, R9);
		CLR(R9, R11);

		// lower area de-active
		scamp5_load_rect(R11, 253, 0, 255, 255);//draw a rectangle in R11
		OR(R9, R10, R11);
		MOV(R10, R9);
		CLR(R9, R11);

		// left area de-active
		scamp5_load_rect(R11, 0, 253, 255, 255);//draw a rectangle in R11
		OR(R9, R10, R11);
		MOV(R10, R9);
		CLR(R9, R11);

		// right area de-active
		scamp5_load_rect(R11, 0, 0, 255, 2);//draw a rectangle in R11
		OR(R9, R10, R11);
		MOV(R10, R9);
		CLR(R9, R11);

		NOT(R10);//logic operation of NOT

		scamp5_output_image(R10, display_3);

		CLR(R9, R11);
		scamp5_kernel_end();

		// Cone Extraction Algorithm 
		size_t count = 0;
		uint8_t event_coords[100][2];//the maxium number of cone events are 100
		uint8_t cone_found[4];//store the boundingbox coordinate
		uint8_t bottom_center[2];//bottom edge center
		int width;//boundingbox width
		int height;//boundingbox height
		double distance;
		int direction = 0;
		int closest_dis = 255;
		int closest_x = 0;
		int closest_y = 0;



		while (scamp5_global_or(R10)) {

			// get first '1' in R10 image
			scamp5_scan_events(R10, event_coords[count], 1);//choose the first right and first up cone

			// put the pixel into R11 and flood using R10 as mask
			scamp5_load_point(R11, event_coords[count][1], event_coords[count][0]);//set the chosen pixel into the same position of R11
			scamp5_flood(R11, R10, 0);//set the pixel in R11 as the flood source, flooding the R10 to select the specific cone whose pixel is chosen

			// R11 now contain the found cone only.

			scamp5_scan_boundingbox(R11, cone_found);//scan the bounding box and save the coordinates in cone_found

			int16_t boundingbox_data[100][4];//max number is 100, store 4 parameters
			boundingbox_data[count][0] = (cone_found[2] + cone_found[0]) / 2;// vertical pos of boundingbox center (X label)
			boundingbox_data[count][1] = (cone_found[3] + cone_found[1]) / 2;// horizontal pos of boundingbox center (Y label)
			boundingbox_data[count][2] = cone_found[2] - cone_found[0];// vertical extent (X label)
			boundingbox_data[count][3] = cone_found[3] - cone_found[1];// horizontal extent (Y label)

			width = boundingbox_data[count][3];//boundingbox width
			height = boundingbox_data[count][2];//boundingbox height
			bottom_center[1] = (cone_found[3] + cone_found[1]) / 2;//Y of bottom edge center 
			bottom_center[0] = cone_found[2];//X of bottom edge center 

			if (50 < bottom_center[0] && bottom_center[0] < 240)//"distant area" limitation is 50 and "forbidden area" limitation is 200
			{
				if (10 < bottom_center[1] && bottom_center[1] < 245)//"safe area" limitation is 50 and 200
				{
					distance = sqrt(pow((255 - bottom_center[0]),2) + pow((127 - bottom_center[1]),2));//distance between robot(255,127) and bottom center

					if (distance < closest_dis)
					{
						closest_dis = distance;//update the closest distance, double to int, lost some accurancy
						closest_x = bottom_center[0];
						closest_y = bottom_center[1];

					}
				}
			}

			if (127 < closest_y && closest_y < 240)//if cone is on the left
			{
				direction = 1;//left
			}
			else if (15 < closest_y && closest_y <= 127)//if cone is on the right
			{
				direction = -1;//right
			}
			else
			{
				direction = 0;//go forward
			}


			//scamp5_display_boundingbox(display_4, &cone_found, 1);//display the boundingbox of found cone
			scamp5_display_boundingbox(display_3, cone_found, 1);//display the boundingbox of found cone
			scamp5_display_boundingbox(display_2, cone_found, 1);//display the boundingbox of found cone
			scamp5_display_boundingbox(display_1, cone_found, 1);//display the boundingbox of found cone
			//scamp5_output_boundingbox(R10, display_2);

			// remove the found cone from R10 to identify other cones
			scamp5_kernel_begin();
			CLR_IF(R10, R11);//CLR_IF (R10, R11) Rl0: = 0 IF R11 = 1, Rl0 : = Rl0 IF R11 = 0
			scamp5_kernel_end();

			// accumulate the counting number 
			count++;

		}


		// send the data to the interface
		static int16_t data[4];
		data[0] = closest_x;// x of closest bottom center
		data[1] = closest_y;// y of closest bottom center
		data[2] = closest_dis;// distance of closest bottom center
		data[3] = direction;// direction of closest bottom center
		printf("closest_x = %d, closest_y = %d, closest_dis = %d, direction = %d\n",data[0],data[1],data[2],data[3]);
		vs_post_int16(data, 1, 4);// send as 1 row 4 column data


		// indicate the attention area and closest cone
		//scamp5_kernel_begin();
		//scamp5_draw_begin(R10);
		//scamp5_draw_line(closest_x, closest_y, 255, 127);//indicate the closest cone
		//scamp5_draw_rect(50, 50, 200, 200);//indicate the attention area
		//scamp5_draw_end;
		//scamp5_kernel_end();


		// readout register image and send to host GUI for display
		if (readout_mode >= 1) {
			scamp5_output_image(R5, display_2);
		}
		if (readout_mode >= 2) {
			scamp5_output_image(C, display_1);
		}
		//if (readout_mode >= 3) {
			//scamp5_output_image(R10, display_3);
		//}

	}

	return 0;
}
