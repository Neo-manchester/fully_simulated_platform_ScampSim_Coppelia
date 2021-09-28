/*!

\file

\ingroup VS_SCAMP5

\author Jianing Chen

*/

#ifndef SCAMP5_KERNEL_API_MACRO_HPP
#define SCAMP5_KERNEL_API_MACRO_HPP


#include "sim_kernel_api.hpp"


namespace scamp5_kernel_api{

    using namespace SCAMP5_PE;


	// Zero
	//------------------------------------------------------------------------------

    /*!
    * @brief 	a := 0
    *
    */
    void res(AREG a);

    /*!
    * @brief 	a := 0, b := 0
    *
    */
    void res(AREG a,AREG b);


	// Basic Arithmetics
	//------------------------------------------------------------------------------

    /*!
    * @brief	y := x0
    *
    */
    void mov( AREG y, ASRC x0 );

    /*!
    * @brief	y := x0 + x1
    *
    */
    void add( AREG y, ASRC x0, ASRC x1 );

    /*!
    * @brief	y := x0 + x1 + x2
    *
    */
    void add( AREG y, ASRC x0, ASRC x1, ASRC x2 );

    /*!
    * @brief	y := x0 - x1
    *
    */
    void sub( AREG y, ASRC x0, ASRC x1 );

    /*!
    * @brief	y := -x0
    *
    */
    void neg( AREG y, ASRC x0 );

    /*!
    * @brief	y := |x0|
    *
    */
    void abs( AREG y, ASRC x0 );



	// Division
	//------------------------------------------------------------------------------

	/*!
	* @brief	y0 := 0.5*x0 + error
	*
	*/
	void divq(AREG y0, ASRC x0);

	/*!
	* @brief	y0 := 0.5*x0; y1 := -0.5*x0
	*
	*/
	void div(AREG y0, AREG y1, AREG y2);

    /*!
    * @brief	y0 := 0.5*x0; y1 := -0.5*x0 + error, y2 := x0 + error
    *
    */
    void div(AREG y0, AREG y1, AREG y2, ASRC x0);

    /*!
    * @brief	y0 := 0.5*y0; y1 := -0.5*y0 + error, y2 := -0.5*y0 + error
    *
    */
    void diva(AREG y0, AREG y1, AREG y2);



	// Neighour Access
	//------------------------------------------------------------------------------

    /*!
    * @brief	y := x0_dir (note: naming of this function is deprecated)
    *
    */
    void mov( AREG y, ASRC x0, const news_t dir );

    /*!
    * @brief	y := x0_dir - x1 (note: naming of this function is deprecated)
    *
    */
    void sub( AREG y, ASRC x0, const news_t dir, ASRC x1 );

	/*!
	 * @brief	y := x0_dir
	 *
	 */
	void movx(AREG y, ASRC x0, const news_t dir);

	/*!
	 * @brief	y := x0_dir_dir (note: this only works when FLAG is "all")
	 *
	 */
	void mov2x(AREG y, ASRC x0, const news_t dir, const news_t dir2);

	/*!
	* @brief	y := x0_dir + x1_dir
	*
	*/
	void addx(AREG y, ASRC x0, ASRC x1, const news_t dir);

	/*!
	 * @brief	y := x0_dir_dir2 + x1_dir_dir2
	 *
	 */
	void add2x(AREG y, ASRC x0, ASRC x1, const news_t dir, const news_t dir2);

	/*!
	 * @brief	y := x0_dir - x1
	 *
	 */
	void subx(AREG y, ASRC x0, const news_t dir, ASRC x1);

	/*!
	 * @brief	y := x0_dir_dir2 - x1
	 *
	 */
	void sub2x(AREG y, ASRC x0, const news_t dir, const news_t dir2, ASRC x1);



	// Image Capture
	//------------------------------------------------------------------------------

    /*!
    * @brief	y := half-range image, and reset PIX
    *
    */
    void get_image( AREG y );

    /*!
    * @brief	y := full-range image, h := half-range image, and reset PIX
    *
    */
    void get_image( AREG y, AREG h );

	/*!
	* @brief 	reset PIX
	*
	*/
	void respix();

	/*!
	* @brief 	reset PIX, keep its reset level in y
	*
	*/
	void respix(AREG y);

	/*!
	* @brief	y := half-range image, supplying the reset level of PIX
	*
	*/
	void getpix(AREG y, AREG pix_res);

	/*!
	* @brief	y := full-range, h := half-range image, supplying the reset level of PIX
	*
	*/
	void getpix(AREG y, AREG h, AREG pix_res);



	// Image Blur
	//------------------------------------------------------------------------------

	/*!
	 * @brief	blur x into y with constant number of iterations (x and y can be same AREG), require R1 and R2 to be set properly
	 *
	 */
    void gauss( AREG y, ASRC x, const int iterations = 3 );

	/*!
	 * @brief	horizontally blur x into y with constant number of iterations (x and y can be same AREG), require R1 and R2 to be set properly
	 *
	 */
	void gaussh(AREG y, ASRC x, const int iterations = 3);

	/*!
	 * @brief	vertically blur x into y with constant number of iterations (x and y can be same AREG), require R1 and R2 to be set properly
	 *
	 */
	void gaussv(AREG y, ASRC x, const int iterations = 3);

	/*!
	 * @brief	blur x into y with constant number of iterations using neighbour mixing (x and y can be same AREG)
	 *
	 */
	void newsblur(AREG y, ASRC x, const int iterations = 1);

	/*!
	 * @brief	horizontally blur x into y with constant number of iterations using neighbour mixing (x and y can be same AREG)
	 *
	 */
	void newsblurh(AREG y, ASRC x, const int iterations = 1);

	/*!
	 * @brief	vertically blur x into y with constant number of iterations using neighbour mixing (x and y can be same AREG)
	 *
	 */
	void newsblurv(AREG y, ASRC x, const int iterations = 1);


};

#endif
