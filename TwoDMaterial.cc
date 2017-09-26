#include <iostream>
#include <cstdlib>
#include <fstream>
#include "TwoDMaterial.h"

using namespace std;

//----------------------------------------
//ADD HERE: Make a constructor with two arguments that sets the width and height
// of the 2D material to be created
//----------------------------------------
TwoDMaterial::TwoDMaterial(int width, int height)
{

   this->width = width;
   this->height = height;
   this->numPhase = 0;

   //You must add the rest of the code
   this->matArray = new float[width*height];
   this->attribArray = new PhaseAttributes[0];


}

//----------------------------------------
//ADD HERE:  Make a destructor for the TwoDMaterial
//----------------------------------------
TwoDMaterial::~TwoDMaterial()
{
  //You must add code here
  delete [] matArray;
  delete [] attribArray;
}

//----------------------------------------
//ADD HERE: Make your own copy constructor
//----------------------------------------
TwoDMaterial::TwoDMaterial(TwoDMaterial & copy) {
   this->width = copy.getWidth();
   this->height = copy.getHeight();
   this->numPhase = copy.getNumPhase();
   this->matArray = new float[width*height];
   this->attribArray = new PhaseAttributes[numPhase];
for (int i = 0; i < width ; i++)
   {
      for (int j = 0; j < height ; j++)
        (*this)(i,j) = (copy)(i,j);
   }
for(int i = 0; i < numPhase; i++) 
  this->attribArray[i] = copy.attribArray[i];

}

//----------------------------------------
//ADD HERE: Make your own assignment operator 
//----------------------------------------
TwoDMaterial & TwoDMaterial::operator=(TwoDMaterial & copy) {
   this->width = copy.getWidth();
   this->height = copy.getHeight();
   this->numPhase = copy.getNumPhase();
   this->matArray = new float[width*height];
   this->attribArray = new PhaseAttributes[numPhase];
for (int i = 0; i < width ; i++)
   {
      for (int j = 0; j < height ; j++)
        (*this)(i,j) = (copy)(i,j);
   }
for(int i = 0; i < numPhase; i++) 
  this->attribArray[i] = copy.attribArray[i];

  return *this;
}
 
//----------------------------------------
//ADD HERE: Overload the prefix ++ operator such that this increases
//the size of attribArrary, which is dynamic, by one element.
//This function will also return a reference to the newly
//added element at the END of the array
//----------------------------------------
PhaseAttributes & TwoDMaterial::operator++()
{
    //remember that you will need to create a new 
    //larger dynamic array and deallocate the old array
    //Insert your code here.
    PhaseAttributes * actualData;

    actualData = new PhaseAttributes[numPhase + 1];

    //first zero out all the volume fraction in actualData;
    for (int i = 0; i < numPhase; i++)
    {
        actualData[i] = attribArray[i];
    }
    delete [] attribArray;
    attribArray = new PhaseAttributes[numPhase + 1];
    attribArray = actualData; ////probably an error/////
    this->numPhase++;
    return (attribArray[numPhase-1]);
}

//----------------------------------------
//I will provide this member function for you. This is a private
//utility function that takes as inputs two locations in
//in the matArray. This function will swap the permittivity
//value for these locations.
//----------------------------------------
void TwoDMaterial::swap(int x1, int y1, int x2, int y2)
{
   float temp;

   temp = (*this)(x1,y1);
   (*this)(x1,y1) = (*this)(x2,y2);
   (*this)(x2,y2) = temp;

}

//----------------------------------------
//ADD HERE: You will need to create this operator such
//it will randomize the material by swapping the permittivity
//values in two locations in the matArray (i.e. use swap 
//function provided to you.  I would suggest
//doing at least 5*width*height number of swaps to produce
//a reasonable degree of randomization of the matArray
//----------------------------------------
TwoDMaterial & TwoDMaterial::operator!()
{ 
   //You will need to add code here
  //srand(time(NULL));
  int x1;
  int y1;
  int x2;
  int y2;
  for(int i = 0; i < 5*width*height; i++) {
      x1 = rand()%(width);
      y1 = rand()%(height);
      x2 = rand()%(width);
      y2 = rand()%(height);
      (*this).swap(x1,y1,x2,y2);
  }
  return *this;
}

//----------------------------------------
//ADD HERE:  You will need to overload this += operator to add materials
//to the material model as seen in main.cc. 
//Add materials essentially means adding to the dynamic array attribArray
//with the approprate permittivity and volumetricFraction.
//HINT: I would encourage you to use the ++ operator overload in this function! 
//----------------------------------------
void TwoDMaterial::operator+=(PhaseAttributes attValue)
{
   //You will need to add code here
  ++(*this) = attValue; ///should I also add to matArray?
}

//----------------------------------------
//ADD HERE:  You will need to overload the parentheses operator
//such that it returns the floating point value of the permittivity.
//Note text in lab about adding const correctness to this lab.
//----------------------------------------
float & TwoDMaterial::operator()(int x, int y)
{
  return(matArray[y*height + x]);

}

//----------------------------------------
//I will provide this function for you. You will need
//to make sure that you provide the overload to the
//parentheses operator to get this working 
//----------------------------------------
void TwoDMaterial::outputMaterialToFile()
{
   string name;

   cout << "Output File Name: ";
   cin >> name;

   ofstream outFile(name, ios::out);

   for (int i = 0; i < width ; i++)
   {
      for (int j = 0; j < height ; j++)
	 outFile << (*this)(i,j) << " " ;
      
      outFile << endl;
   }
   
   outFile.close();
}

//----------------------------------------
//ADD HERE:
//You will need to make sure that you create this composite
//material with the approprate permittivites and 
//volume fractions given by the client in main.
//HINT: I would encourage you to call the ! operator on the
//data at the end of this function to help you create a randomize material.
//----------------------------------------

void TwoDMaterial::createMixNanocomposite()
{

   //This assumes that volumetric fraction add to one
   float sum = 0.0;
   for (int i=0;i<numPhase;i++)
	sum += attribArray[i].getVolumetricFraction();

   if (sum == 1.0) //then okay
   {
    int j = 0;
    int k = 0;
    for(int i = 0; i < numPhase; i++) {
      while (j < attribArray[i].getVolumetricFraction()*width*height + k) {
        matArray[j] = attribArray[i].getPermittivity();
        j++;
      }
      j = attribArray[i].getVolumetricFraction()*width*height;
      k = attribArray[i].getVolumetricFraction()*width*height;
    }
   //you must add code here to get a proper mix of materials
    !(*this);
   }    
   else //there is an error
   {
	cerr << "The volumetric fractions do not add to one" << endl;
   }

}

//----------------------------------------
// I will provide this function for you.  You must
//be able to get your code working with this function
//----------------------------------------
void TwoDMaterial::extractStatistics()
{

    PhaseAttributes * actualData;

    actualData = new PhaseAttributes[numPhase];

    //first zero out all the volume fraction in actualData;
    for (int i = 0; i < numPhase; i++)
    {
        actualData[i].setPermittivity(attribArray[i].getPermittivity());
	actualData[i].setVolumetricFraction(0.0);
    }

    //let's start with accumulating numbers first. I will temporary keep
    //the count of each permittivity in the volumetricFraction variable
    for (int i =0; i < width; i++)
        for (int j = 0; j < height; j++)
	{
	   for (int k = 0; k < numPhase; k++)
	   {   if ((*this)(i,j) == actualData[k].getPermittivity()) 
			actualData[k].setVolumetricFraction(actualData[k].getVolumetricFraction()+1.0);
	   }

	} 

   //now transform this count in to fraction data for volumetricFraction  
    for (int i = 0; i < numPhase; i++)
    {
	actualData[i].setVolumetricFraction(actualData[i].getVolumetricFraction()/(width*height));
    }

    //Let's print the data to the screen for review
    for (int i = 0; i < numPhase; i++)
    {
        cout << "k = " << actualData[i].getPermittivity() << 
	" f_target = " << attribArray[i].getVolumetricFraction() << 
	" f_act = " << actualData[i].getVolumetricFraction() << endl;
    }

    //remember to delete data that was dynamically allocated
    delete [] actualData;
}

//----------------------------------------
//add the setter and getter implementations here
//----------------------------------------
int TwoDMaterial::getWidth() {
  return width;
}
int TwoDMaterial::getHeight() {
  return height;
}
float * TwoDMaterial::getMatArray() {
  return matArray;
}
PhaseAttributes * TwoDMaterial::getAttribArray() {
  return attribArray;
}
int TwoDMaterial::getNumPhase() {
  return numPhase;
}
TwoDMaterial & TwoDMaterial::setWidth(int w) {
  this->width = w;
  return *this;
}
TwoDMaterial & TwoDMaterial::setHeight(int h) {
  this->height = h;
  return *this;
}
TwoDMaterial & TwoDMaterial::setMatArray(float * ma) {
  this->matArray = ma; /////////////////////////possible error///////////
  return *this;
}
TwoDMaterial & TwoDMaterial::setAttribArray(PhaseAttributes * attr) {
  this->attribArray = attr; /////////////////////////possible error///////////
  return *this;
}
TwoDMaterial & TwoDMaterial::setNumPhase(int num) {
  this->numPhase = num;
  return *this;
}





