#include "itkVectorImage.h"
#include "itkImageRegionIterator.h"
#include "itkNthElementImageAdaptor.h"
#include "itkThresholdImageFilter.h"
#include "itkBinomialBlurImageFilter.h"

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
 
  // Adaptor
  unsigned int componentIndex = 0;
  typedef itk::NthElementImageAdaptor<VectorImageType, PixelType> AdaptorType;
  AdaptorType::Pointer adaptor = AdaptorType::New();
  adaptor->SelectNthElement(componentIndex);
  adaptor->SetImage(image);
  adaptor->Modified();
  adaptor->Update();

  // Thresholder
  typedef itk::ThresholdImageFilter<AdaptorType> ThresholderType;
  typename ThresholderType::Pointer thresholder = ThresholderType::New();
  PixelType th = 10;
  
  // This segfault
  //thresholder->SetInput(adaptor);
  //thresholder->ThresholdAbove(th);
  //thresholder->SetOutsideValue(th);
  //thresholder->Update();

  // This works
  typedef itk::BinomialBlurImageFilter<AdaptorType, ScalarImageType >  BlurFilterType;
  BlurFilterType::Pointer blurFilter = BlurFilterType::New();
  blurFilter->SetInput(adaptor);
  blurFilter->Update();

  return EXIT_SUCCESS;
}
 
