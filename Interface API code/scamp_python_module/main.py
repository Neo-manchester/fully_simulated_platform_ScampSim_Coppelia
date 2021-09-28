# ******************************************************************
# WEN FAN Dissertation Program
#
# ******************************************************************
#
# Example 25 - Python interface from scamp_sim and Python Remote API with CoppeliaSim
#
# ******************************************************************

# Make sure to have ScampSim server running, with CoppeliaSim environment scene loaded
#
# Do not launch CoppeliaSim simulation, and make sure that the B0 resolver
# is running. Then run this script
#
# The client side (i.e. this script) depends on:
#
# b0RemoteApi (Python script), which depends several libraries present
# in the folder


# preliminary for interface

import io
import time
import scamp
import tkinter as tk
from PIL import Image, ImageTk

# preliminary for B0Remote API

import b0RemoteApi
import time
import math
import numpy as np

# ***************************************************************
# initialization  interface to receive massage from scamp_sim (A)
# ***************************************************************

closest_x = [0]  # define a list of global value
closest_y = [0]
closest_dis = [255]
direction = [0]
real_dis = [10.000]
real_theta = [0.000]
real_x = [0]
real_y = [127]
# data = [0, 0, 0, 0]

def process_packet(packet):  # define how to process the packet
    global DisplayCanvas
    global DisplayImage

    # time.sleep(0.05)  # delay 0.05s


    print(packet['type'])
    if packet['type'] == 'data':

        lc = packet['loopcounter']
        datatype = packet['datatype']

        # print(lc, datatype)

        if datatype == 'TEXT':
            print('[%d] text: %s' % (lc, repr(packet['text'])))
            # None

        elif datatype == 'INT16':
            data = np.array(packet['data'])
            print(data)
            closest_x[0] = data[0, 0]
            closest_y[0] = data[0, 1]
            closest_dis[0] = data[0, 2]
            direction[0] = data[0, 3]
            # print('[%d] int16 %dx%d >> %d' % (lc, packet['n_rows'], packet['n_cols'], packet['channel']))

        elif datatype == 'INT32':
            print('[%d] int32 %dx%d >> %d' % (lc, packet['n_rows'], packet['n_cols'], packet['channel']))
            # print(packet['data'])

        elif datatype == 'FLOAT':
            print('[%d] float %dx%d >> %d' % (lc, packet['n_rows'], packet['n_cols'], packet['channel']))

        elif datatype == 'REQUEST':

            if packet['filetype'] ==  'IMAGE':
                print('[%d] request image %s %d' % (lc, repr(packet['filepath']), packet['n_bits']))
                img = Image.open(packet['filepath']).transpose(Image.FLIP_TOP_BOTTOM)
                scamp.send_image(img.tobytes(), img.width, img.height, packet['n_bits'])

            elif packet['filetype'] ==  'FILE':
                print('[%d] request file %s' % (lc, repr(packet['filepath'])))
                with open(packet['filepath'], "rb") as f:
                    scamp.send_file(f.read())

    else:
        print('packet: type=%s, size=%d' % (packet['type'], packet['size']))


def slider_1_callback(value):
    scamp.send_gui_value(0, int(value))


def check_1_callback():
    global Check_1_Var
    global Send_Msg_On_Quit
    if Check_1_Var.get():
        scamp.send_message(scamp.VS_MSG_HOST_ON, 0, 0)
        Send_Msg_On_Quit = True
    else:
        scamp.send_message(scamp.VS_MSG_HOST_DC, 0, 0)
        Send_Msg_On_Quit = False

count_i = [0]  # count the target number
def main_process():  # define the main function (A+B)


    #while True:   # reaction navigation please use this part
        #packet = scamp.get_packet()  # get packet frm scamp_sim
        #if packet is None:
            #break
        #else:
            #process_packet(packet)  # turn to the packet processing

            ## Control Algorithm
            #K = direction[0] * (70 / closest_dis[0])

            #steer_target = math.radians(-20 * K)  # turn left with 30 degrees, left(+), right(-)

            #print(20 * K)

            #client.simxSetJointPosition(steer_joint_Handle, steer_target, client.simxServiceCall())  # set steer angle

            ## B0 Remote API loop
            #stepSimulation()

    #tk_root.update_idletasks()

    #tk_root.after(1, main_process)



    while True:  # single target navigation and multiple target navigation please use this part

        packet = scamp.get_packet()  # get packet frm scamp_sim
        if packet is None:
            break
        else:
            process_packet(packet)  # turn to the packet processing

            ## obs_data = [closest_x, closest_y, closest_dis]  # please ignore this mapping part
            ## obs_data = [10, 10, 0]
            ## client.simxSetArrayParameter("obstacle_data", obs_data, client.simxServiceCall())

            ##if closest_dis[0] > 245:
                ##real_dis[0] = 10
            ##elif closest_dis[0] > 243:
                ##real_dis[0] = 9.375
            ##elif closest_dis[0] > 240:
                ##real_dis[0] = 8.75
            ##elif closest_dis[0] > 238:
                ##real_dis[0] = 8.125
            ##elif closest_dis[0] > 235:
                ##real_dis[0] = 7.5
            ##elif closest_dis[0] > 225:
                ##real_dis[0] = 6.875
            ## closest_dis[0] > 220:
                ##real_dis[0] = 6.25
            ##elif closest_dis[0] > 215:
                ##real_dis[0] = 5.625
            ##elif closest_dis[0] > 200:
                ##real_dis[0] = 5
            ##elif closest_dis[0] > 185:
                ##real_dis[0] = 4.375
            ##elif closest_dis[0] > 170:
                ##real_dis[0] = 3.75
            ##elif closest_dis[0] > 140:
                ##real_dis[0] = 3.125
            ##elif closest_dis[0] > 97:
                ##real_dis[0] = 2.5
            ##elif closest_dis[0] > 8:
                ##real_dis[0] = 1.875
            ##else:
                ##real_dis[0] = 1.25

            ##real_theta_o = math.atan2(127 - closest_y[0], 255 - closest_x[0])

            ##x_target = 20
            ##y_target = 20

            ##err, pos = client.simxGetObjectPosition(body_dummy_Handle, -1, client.simxServiceCall())
            ##x_robot = pos[0]
            ##y_robot = pos[1]
            ##theta_target = math.atan2(y_target - y_robot, x_target - x_robot)

            ##real_theta[0] = theta_target - real_theta_o

            ##real_x_o = real_dis[0] * math.cos(real_theta[0])
            ##real_y_o = real_dis[0] * math.sin(real_theta[0])

            ##real_x = real_x_o + x_robot
            ##real_y = real_y_o + y_robot

            ##client.simxSetIntSignal("pos_x", real_x, client.simxServiceCall())
            ##client.simxSetIntSignal("pos_y", real_y, client.simxServiceCall())
            ## client.simxSetIntSignal("pos_dis", closest_dis, client.simxServiceCall())

            if closest_dis[0] > 200:  # D_safe

                x_target = [10, 15, 17, 0]
                y_target = [16, 15, 6, 0]

                print(count_i)

                err, pos = client.simxGetObjectPosition(body_dummy_Handle, -1, client.simxServiceCall())
                x_robot = pos[0]
                y_robot = pos[1]

                theta_target = math.atan2(y_target[count_i[0]] - y_robot, x_target[count_i[0]] - x_robot)

                dis_e = np.sqrt(pow(x_target[count_i[0]] - x_robot, 2) + pow(y_target[count_i[0]] - y_robot, 2))

                if dis_e > 1:  # E_safe

                    err, theta_robot = client.simxGetObjectOrientation(body_dummy_Handle, -1, client.simxServiceCall())

                    theta_steer = theta_target - theta_robot[2]

                    client.simxSetJointPosition(steer_joint_Handle, theta_steer, client.simxServiceCall())

                    stepSimulation()

                    break

                else:

                    if count_i[0] < len(x_target)-1:  # update the count of target
                        count_i[0] = count_i[0] + 1
                    else:
                        count_i[0] = len(x_target)-1

                    print(count_i)
                    motor_velocity = 0
                    client.simxSetJointTargetVelocity(motor_joint_Handle, motor_velocity, client.simxServiceCall())
                    brake_force = 100
                    client.simxSetJointForce(fr_brake_Handle, brake_force, client.simxServiceCall())
                    client.simxSetJointForce(fl_brake_Handle, brake_force, client.simxServiceCall())
                    client.simxSetJointForce(br_brake_Handle, brake_force, client.simxServiceCall())
                    client.simxSetJointForce(bl_brake_Handle, brake_force, client.simxServiceCall())

                    stepSimulation()

            else:
                # Control Algorithm
                K = direction[0] * (100 / closest_dis[0])  # K_safe

                steer_target = math.radians(-20 * K)  # K_steer

                print(20 * K)

                client.simxSetJointPosition(steer_joint_Handle, steer_target,
                                            client.simxServiceCall())  # set steer angle

                # B0 Remote API loop
                stepSimulation()

    tk_root.update_idletasks()

    tk_root.after(1, main_process)




# *************************************************
# Initialization of B0Remote API to CoppeliaSim (B)
# *************************************************

with b0RemoteApi.RemoteApiClient('b0RemoteApi_pythonClient', 'b0RemoteApi') as client:
    client.doNextStep = True
    client.runInSynchronousMode = True


    def simulationStepStarted(msg):  # call back function of simulation step start
        simTime = msg[1][b'simulationTime']
        print('Simulation step started. Simulation time: ', simTime)


    def simulationStepDone(msg):  # call back function of simulation step done
        simTime = msg[1][b'simulationTime']
        print('Simulation step done. Simulation time: ', simTime)
        client.doNextStep = True  # this step is done, so next step is acceptable


    def stepSimulation():  # function of simulation step
        if client.runInSynchronousMode:
            while not client.doNextStep:  # while doNextStep is false
                client.simxSpinOnce()   # Calls all callbacks for subscribers that have messages waiting, then returns
            client.doNextStep = False  # if doNextStep is true, set it false
            client.simxSynchronousTrigger()  # Triggers next simulation step, if synchronous mode was previously enabled
        else:
            client.simxSpinOnce()  # if not run in synchronous mode, calls all callbacks


# Entry Point (A)

    Connection_Type = 'TCP'  # TCP for host or USB for scamp5

    tk_root = tk.Tk()
    tk_root.title('Scamp5d Python App')

    W = 256
    H = 256

    N_Display = 2
    DisplayImage = []
    DisplayCanvas = []
    for i in range(N_Display):
        image = ImageTk.PhotoImage(Image.frombytes(mode='L', size=(W, H), data=bytes(W*H)))
        DisplayImage.append(image)
        canvas = tk.Canvas(tk_root, width=W, height=H, bd=0)
        DisplayCanvas.append(canvas)
        canvas.pack()
        canvas.create_image(0, 0, image=DisplayImage[i], anchor=tk.NW)

    Slider_1 = tk.Scale(tk_root, from_=-100, to=100, orient=tk.HORIZONTAL, command=slider_1_callback)
    Slider_1.pack()

    Send_Msg_On_Quit = False
    if Connection_Type == 'USB':
        Check_1_Var = tk.IntVar()
        Check_1 = tk.Checkbutton(tk_root, text="vs_gui_is_on()", variable=Check_1_Var, command=check_1_callback)
        Check_1.pack()
        print('open USB connection...')
        scamp.open_usb('0')
    else:
        print('open TCP connection...')
        scamp.open_tcp('127.0.0.1',27888)

    # ***************************************
    # The main loop of whole processing (A+B)
    # ***************************************

    # API and Control (B)
    client.simxAddStatusbarMessage('Hello world from Python!', client.simxDefaultPublisher())

    if client.runInSynchronousMode:
        client.simxSynchronous(True)

    client.simxGetSimulationStepStarted(client.simxDefaultSubscriber(simulationStepStarted))  # step start
    client.simxGetSimulationStepDone(client.simxDefaultSubscriber(simulationStepDone))  # step done

    res, steer_joint_Handle = client.simxGetObjectHandle('steer_joint', client.simxServiceCall())  # get steer handle
    res, body_dummy_Handle = client.simxGetObjectHandle('body_dummy', client.simxServiceCall())  # get body handle
    res, motor_joint_Handle = client.simxGetObjectHandle('motor_joint', client.simxServiceCall())  # get motor handle
    res, fr_brake_Handle = client.simxGetObjectHandle('fr_brake_joint', client.simxServiceCall())  # get fr brake handle
    res, fl_brake_Handle = client.simxGetObjectHandle('fl_brake_joint', client.simxServiceCall())  # get fl brake handle
    res, br_brake_Handle = client.simxGetObjectHandle('br_brake_joint', client.simxServiceCall())  # get br brake handle
    res, bl_brake_Handle = client.simxGetObjectHandle('bl_brake_joint', client.simxServiceCall())  # get bl brake handle

    client.simxStartSimulation(client.simxDefaultPublisher())  # simulation start

    # interface (A)
    scamp.routine()

    startTime = time.time()
    while 1:  # run main_process always
    #while time.time() < startTime + 150:  # simulation time is 15(s)
        main_process()  # the main loop (A+B)
        tk_root.mainloop()


    # *******************
    # Close the main loop
    # *******************

    #if Send_Msg_On_Quit:
        #scamp.send_message(scamp.VS_MSG_HOST_DC, 0, 0)

    #time.sleep(0.05)
    #scamp.close()  # interface close
    #client.simxStopSimulation(client.simxDefaultPublisher())  # API close
    #print('End.')

    #exit()

