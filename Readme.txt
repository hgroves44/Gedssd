This is a text file to explain the geometry file for the gedssd and clovers around it. 

There are 6 different logical volumes, 4 for the gedssd and 2 for the clover. The Gedssd consists of a cryo chamber, caps for that chamber, and a thin and thick Ge detector. The clover is made up of 4 crystals next to each other, and a cryo chamber around them all. There are 8 crystals pointing in towards the Gedssd around the side, and one sitting behind it on the z axis. 

Dimensions for all of the parts were gotten from a file sent to me by Dr. Kyle Leach from the Decay Station Collaboration. 

The PlaceDetector funciton is where I place the assemblys in the world volume. All of the clovers are put in the same distance back from the gedssd in the z direciton, but 8 are rotated 90 deg down from the z axis, and then rotated around the 360 degree circle in the x-y plane. Then, the clovers are rotated around their own local axes to be facing in toward the gedssd in the center. As of now, there is going to be 9 no matter how many detectors you put in as a command. The next upgrade is to make it so that the number of clovers placed is dependent on the number put in the run macro when visulizing. For now, there will only be one gedssd. This may change depending on the needs of the project.

The build function contians all of the commands necessary to get the materials, visual attributes, and logical volumes for the gedssd and clover. 
