#include "FilteredBackProjection.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

NumSurface* FilteredBackProjection( ImageArray& array, int Nres, double (*kernal)(int,double))
{
    // Nres is the resolution for the reconstructed surface.
    const double range = array.GetRange();

    array.ConvolveWithKernal(kernal);	// filtered
    NumSurface* rec = new NumSurface(Nres,range,Nres,range);
    int Nangle = array.GetSize();
    for(int ll=0; ll<Nangle; ll++){	// iterate over all angle of view
        double angle = array.GetAngle(ll);
        for( int i=0; i<Nres; i++){	// loop over X-coordinate
            double x = -range + i*2*range/(Nres-1);
            for( int j=0; j<Nres; j++){	// loop over y-coordinate
                double y = -range + j*2*range/(Nres-1);
                double t = x*cos(angle) + y*sin(angle);	// distance to origin for angle ll.
                (*rec)(i,j) += (array.GetFilteredCurve(ll))(t,0)*pi/Nangle; // superpose the value, assuming uniform grid.
            }
        }
    }
    return rec;
}

NumVolume* FilteredBackProjection3D( ImageArray& array, int Nres,double (*kernal)(int,double))
{
    const double range = array.GetRange(); //this is the same as 2D since we are considering slice by slice
    const double rangeZ = array.GetRangeZ(); // this is the maximum domain height.
    //std::cerr << "range is " << range <<std::endl;
    //std::cerr << "rangeZ is " << rangeZ<<std::endl;

    int Nslice = array.GetSlice(); //Nslice is the slice number of horizontal slice
    std::cerr << "Nslice is " << Nslice<<std::endl;
    array.ConvolveWithKernal(kernal); //filtered
    std::cerr << "convolution done" << std::endl;
    double*** w;
    w = new double**[Nres];
    for(int i=0;i<Nres;i++){
        w[i] = new double*[Nres];
        for(int j=0;j<Nres;j++){
            w[i][j] = new double[Nslice];
        }
    }
    int Nangle = array.GetSize(); //Nangle is slice*size number of angle views
    int NviewPerslice = Nangle/Nslice; // NviewPerslice is the total number of angle view per slice. Assuming each slice has the same number of angle view for now.
    double sum[Nres][Nres];
    for(int k=0;k<Nslice;k++){ //iterate over number of horizontal slice
        for(int i=0;i<Nres;i++){
            for(int j=0;j<Nres;j++){
                sum[i][j] =0;
            }
        }
        std::cerr<< "k is" << k << std::endl;
        for(int ll=0; ll<NviewPerslice; ll++){ // iterate over angle of view per slice
            double angle = array.GetAngle(ll+k*NviewPerslice);
            for( int i=0; i<Nres; i++){	// loop over x-coordinate
                double x = -range + i*2*range/(Nres-1);
                for( int j=0; j<Nres; j++){	// loop over y-coordinate
                    double y = -range + j*2*range/(Nres-1);
                    double t = x*cos(angle) + y*sin(angle);	// distance to origin for angle ll.
                    //std::cerr<< "t is" << t << std::endl;
                    NumCurve temp_Curve = (array.GetFilteredCurve(ll+k*NviewPerslice));
                    int size_y = temp_Curve.GetSize()/Nslice;
                    //std::cerr<< "size_y is" << size_y << std::endl;
                    NumCurve temp_Slice = NumCurve(size_y);
                    temp_Slice.SetRange(range);
                    double* yy = temp_Slice.GetYPtr();
                    double* xx = temp_Slice.GetXPtr();
                    double* Y = temp_Curve.GetYPtr();
                    double* X = temp_Curve.GetXPtr();
                    //std::cerr<< "running1" << std::endl;
                    for(int q=0;q<size_y;q++){
                        double tempy = Y[q+k*size_y];
                        double tempx = X[q];
                        //std::cerr<< "tempx " << tempx << "tempy " << tempy<<std::endl;
                        yy[q] = tempy;
                        xx[q] = tempx;
                    }
                    //std::cerr<< "running2" << std::endl;
                    sum[i][j] += (temp_Slice)(t,0)*pi/NviewPerslice;
                    //std::cerr<< "running3" << std::endl;
                   // superpose the value, assuming uniform grid.
                } // i loop
            }// j loop
        }    // ll loop
        //std::cerr<< "sum is" << sum[50][50]<< std::endl;
        for( int ii=0; ii<Nres; ii++){	// loop over x-coordinate
            for( int jj=0; jj<Nres; jj++){	// loop over y-coordinate
                w[ii][jj][k] = sum[ii][jj];
            }
        }
        //std::cerr<< "sum is" << sum[50][50]<< std::endl;
    }// k loop
   NumVolume* rec = new NumVolume(Nres,range,Nres,range,Nslice,rangeZ,w);
   for (int i = 0; i < Nres; ++i) {
        for (int j = 0; j < Nres; ++j)
            delete [] w[i][j];
        delete [] w[i];
    }
    delete [] w;
    return rec;
}
