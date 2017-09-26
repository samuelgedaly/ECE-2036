#include "TwoDMaterial.h"
//#include "PhaseAttr.h"
#include <ctime>


int main()
{
   srand(time(0));

   //define the constituents that you would like to mix
   PhaseAttributes att1(2.0,0.7);
   PhaseAttributes att2(50.0,0.2);
   PhaseAttributes att3(25.0,0.1);

   //instantiate the composite material you would like to create
   TwoDMaterial mat1(100,100);

   //add each constituents to the mat1 object
   mat1+=att1;
   mat1+=att2;
   mat1+=att3;

   //Now actually mix the constituent materials together
   mat1.createMixNanocomposite();

   //Ouput the material to a file that can be read by MATLAB
   mat1.outputMaterialToFile();

   //Confirm that composite material has the appropriate volumetric fraction
   mat1.extractStatistics();

   //randomize the material again and output the result to a file
   (!mat1).outputMaterialToFile();

   //Confirm that the composite material has the appropriate volumetric fraction
   mat1.extractStatistics();

   //instantiate a second composite material you would like to create with larger field
   TwoDMaterial mat2(500,500);

   //add constituent materials to the composite called mat2
   mat2+= (att1 = PhaseAttributes(4.2,0.1));
   mat2+= (att2 = PhaseAttributes(11.9,0.9));
 
   //mix these constituent materials together 
   mat2.createMixNanocomposite();

   //output the material mat2 to an output file 
   mat2.outputMaterialToFile();

   //confirm that the composite material mat2 has the appropriate volumetric fraction
   mat2.extractStatistics();
 
} 
