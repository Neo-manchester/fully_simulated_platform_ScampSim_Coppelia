# Fully_simulated_platform_ScampSim_Coppelia
The fully simulated platform of ScampSim and Coppelia. Including three parts of codes, ScampSim server(c++); Interface &amp; API (Python); CoppeliaSim scene (Lua).

1. The related Scamp5d system documents, guidances and downloads files could be found via https://scamp.gitlab.io/scamp5d_doc/. Before the next operation, the ScampSim Server and Scamp Host should be installed on your equipment. Also, the CoppeliaSim simulator could be found here https://www.coppeliarobotics.com/, whose latest released version is 4.2.0.

2. In the 'ScampSim code' folder, the C file 'main.cpp' contains the Flood image processing algorithm which could be run in the ScampSim Server. Configuration settings are     included in '~.json' file, for example, the type of image source.

3. In the 'Interface API code' folder, the Python file 'main.py' contains the interface module and remote API module to comunicate the ScampSim and CoppeliaSim. 

4. In the 'CoppeliaSim code' folder, three CoppeliaSim files '~.tt' provide different simulation environments for corresponding tasks and configured Manta robot inside.

5. Noticed that, at least two screens are needed. The runing order is (1) Server (always be sure of B0resover running); (2) Interface & API ;(3) CoppeliaSim (automaticaly launched by API)
