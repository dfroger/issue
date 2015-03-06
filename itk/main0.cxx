#include "itkVectorImage.h"
#include "itkImageAdaptor.h"
#include "itkImageRegionIterator.h"
#include "itkNthElementImageAdaptor.h"
#include "itkComposeImageFilter.h"
#include "itkThresholdImageFilter.h"
#include "itkImageDuplicator.h"

using namespace std;

const unsigned int ImageDimension = 2;
const unsigned int NumberOfComponents = 2;
const unsigned int ImageSize = 4;
typedef float PixelType;
typedef itk::Image<PixelType, ImageDimension> ScalarImageType;
typedef itk::VectorImage<PixelType, ImageDimension> VectorImageType;
typedef itk::ImageRegionIterator<VectorImageType> IteratorType;
typedef itk::VariableLengthVector<PixelType> VariableVectorType;
 
void
CreateImage(VectorImageType::Pointer image)
{
  VectorImageType::IndexType start;
  start.Fill(0);
 
  VectorImageType::SizeType size;
  size.Fill(ImageSize);
 
  VectorImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
 
  image->SetRegions(region);
  image->SetVectorLength(NumberOfComponents);
  image->Allocate();
 
  VectorImageType::IndexType index;
  VariableVectorType value;
  value.SetSize(NumberOfComponents);
  IteratorType ImageIt(image, image->GetLargestPossibleRegion());
  for(ImageIt.GoToBegin(); !ImageIt.IsAtEnd(); ++ImageIt) {
    index = ImageIt.GetIndex();
    unsigned int ix = index[0];
    unsigned int iy = index[1];
    float x = float (ix) / float(ImageSize); // x is in [0,1]
    float y = float (iy) / float(ImageSize); // y is in [0,1]
    //value[0] = cos(x)*sin(y);
    //value[1] = sin(x)*cos(y);
    value[0] = iy*10 + ix;
    value[1] = iy*10 + ix + 1;
    ImageIt.Set(value);
  }
}

template<typename ImageType>
void
PrintImage(typename ImageType::Pointer image)
{
  typedef itk::ImageRegionIterator<ImageType> IteratorType;
  IteratorType ImageIt(image, image->GetLargestPossibleRegion());
  VectorImageType::IndexType index;
  for(ImageIt.GoToBegin(); !ImageIt.IsAtEnd(); ++ImageIt) {
      index = ImageIt.GetIndex();
      unsigned int ix = index[0];
      unsigned int iy = index[1];
      cout << "image[" << ix << "," << iy << "] " << ImageIt.Get() << endl;
  }
}
 
int main()
{
  VectorImageType::Pointer image = VectorImageType::New();
  CreateImage(image);

  cout << "Input:" << endl;
  PrintImage<VectorImageType>(image);

  // Threshold value
  //PixelType th = 0.5;
  VariableVectorType th;
  th.SetSize(NumberOfComponents);
  th[0] = 0.5;
  th[1] = 0.5;

  // Thresholder
  typedef itk::ThresholdImageFilter<VectorImageType> ThresholderType;
  typename ThresholderType::Pointer thresholder = ThresholderType::New(); // Error here

  thresholder->SetInput(image);
  thresholder->ThresholdAbove(th);
  thresholder->SetOutsideValue(th);

  cout << "Output:" << endl;
  VectorImageType::Pointer imageout = composer->GetOutput();
  PrintImage<VectorImageType>(imageout);

  return EXIT_SUCCESS;
}
 
