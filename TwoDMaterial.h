#include <iostream>
#include "PhaseAttr.h"

class TwoDMaterial
{
  public:
    //constructors
    TwoDMaterial(int=100, int=100);
    ~TwoDMaterial();
    //ADD HERE: I would like for you to add a copy constructor prototype
    TwoDMaterial(TwoDMaterial & tdmat);
    //operator overloads that can be used by client
    void operator+=(PhaseAttributes); //add phase to composite
    TwoDMaterial & operator!(); //This will randomize the material array
    PhaseAttributes & operator++(); //adds one to permittivity array length 
    float & operator()(int,int); //used to access matArray elements

    //ADD HERE: I would like for you to add an assignment operator prototype
    TwoDMaterial & operator=(TwoDMaterial &);
    //public member functions need by client
    void extractStatistics();
    void createMixNanocomposite();
    void outputMaterialToFile(); 

    //getters 
    int getWidth() ; 
    int getHeight() ; 
    //ADD HERE: complete the set of getter functions  
    float * getMatArray() ;
    PhaseAttributes * getAttribArray() ;
    int getNumPhase() ; 
    //setters
    TwoDMaterial & setWidth(int);     
    TwoDMaterial & setHeight(int);     
    //ADD HERE: complete the set of setter functions
    TwoDMaterial & setMatArray(float *);
    TwoDMaterial & setAttribArray(PhaseAttributes *);
    TwoDMaterial & setNumPhase(int);
    //utility functions
  private:
    void swap(int,int,int,int);

  private:
    int width;
    int height;
    float * matArray; 
    PhaseAttributes * attribArray;
    int numPhase;
};


