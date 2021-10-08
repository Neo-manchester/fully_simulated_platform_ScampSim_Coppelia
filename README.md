# Fully_simulated_platform_ScampSim_Coppelia
The monocular vision-based robot navigation in a fully simulated platform of ScampSim and Coppelia. Including three parts of codes, ScampSim server(c++); Interface &amp; API (Python); CoppeliaSim scene (Lua).

1. The related Scamp5d system documents, guidances and downloads files could be found via https://scamp.gitlab.io/scamp5d_doc/. Before the next operation, the ScampSim Server and Scamp Host should be installed on your equipment. Also, the CoppeliaSim simulator could be found here https://www.coppeliarobotics.com/, whose latest released version is 4.2.0.

2. In the 'ScampSim code' folder, the C file '\ScampSim code\scamp5d_sim_1_0_0\scamp5d_sim\sim_example\main.cpp' contains the Flood image processing algorithm which could be run in the ScampSim Server. Configuration settings are included in 'sim_config.json' file, for example, the type of image source. Since the copyright issue, please download the related documents through the Scamp official website https://scamp.gitlab.io/scamp5d_doc/.

3. In the 'Interface API code' folder, the Python file '\Interface API code\scamp_python_module\main.py' contains the interface and remote API module to comunicate the ScampSim and CoppeliaSim. Also, the navigation algorithm part is included inside. For your customised design, this module could be improved because it is originaly rewrited from the interface library template. You can delete some needless codes such as TK inter as your special requirement and design the new cycle, or place the navigation part into the CoppeliaSim.

4. In the 'CoppeliaSim code' folder, three CoppeliaSim files '~.ttt' provide different simulation environments for corresponding tasks and configured Manta robot inside.

5. Noticed that, at least two screens are needed. The runing order is (1) Server (always be sure of B0resover running); (2) Interface & API ;(3) CoppeliaSim (automaticaly launched by API)

6. All the Scamp-related copyrights are reserved by the University of Manchester. If there is a copyright infringement problem in my file, please contact me to delete it
