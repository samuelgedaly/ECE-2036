#include <iostream>

class PhaseAttributes
{
 public:

 PhaseAttributes(float, float); //Sets permittivity and volumetricFraction
 PhaseAttributes(); //Set permittivity and volumetricFraction to initial values of 1
 // You will need to define the getters and setters for this class.
 //Make the setter functions so that they can be cascaded
 float getPermittivity(); 
 float getVolumetricFraction();
 PhaseAttributes & setPermittivity(float);     
 PhaseAttributes & setVolumetricFraction(float);   

 private:
 float permittivity;
 float volumetricFraction;
};