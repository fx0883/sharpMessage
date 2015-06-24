//
//  Util.h
//  SharpMessage
//
//  Created by apple on 6/24/15.
//
//

#ifndef __SharpMessage__Util__
#define __SharpMessage__Util__

#include <stdio.h>
#include <math.h>
#include <iostream.h>
#include <string.h>

//Round(1.234,2) = 1.23
//Round(1.234,0) = 1.0
//Round(123.4,-1) = 120.0
double Round(double dVal, short iPlaces) {
    double dRetval;
    double dMod = 0.0000001;
    if (dVal<0.0) dMod=-0.0000001;
    dRetval=dVal;
    dRetval+=(5.0/pow(10.0,iPlaces+1.0));
    dRetval*=pow(10.0,iPlaces);
    dRetval=floor(dRetval+dMod);
    dRetval/=pow(10.0,iPlaces);
    return(dRetval);
};

//double round(double dVal, short iPlaces) //iPlaces>=0
//{
//    unsigned char s[20];
//    double dRetval;
//    
////    sprintf(s,"%.*lf",iPlaces,dVal);
////    sscanf(s,"%lf",&dRetval);
//    return Round(dRetval);
//}

#endif /* defined(__SharpMessage__Util__) */
