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
 
  // Adaptor
  typedef itk::NthElementImageAdaptor<VectorImageType, PixelType> AdaptorType;
  AdaptorType::Pointer adaptor = AdaptorType::New();
  adaptor->SetImage(image);

  // Thresholder
  typedef itk::ThresholdImageFilter<AdaptorType> ThresholderType;
  typename ThresholderType::Pointer thresholder = ThresholderType::New();
  //VariableVectorType th;
  //th.SetSize(NumberOfComponents);
  //th[0] = 0.5;
  //th[1] = 0.5;
  PixelType th = 0.5;

  // Duplicator.
  typedef itk::ImageDuplicator<AdaptorType> DuplicatorType;
  typename DuplicatorType::Pointer duplicator = DuplicatorType::New();

  // Composer
  typedef itk::ComposeImageFilter<AdaptorType> ComposerType;
  typename ComposerType::Pointer composer = ComposerType::New();

  for (unsigned int componentIndex = 0 ;
                    componentIndex < NumberOfComponents ; 
                    componentIndex++)
  {
      adaptor->SelectNthElement(componentIndex);
      adaptor->Modified();
      adaptor->Update();

      //PrintImage<AdaptorType>(adaptor);
      //thresholder->SetInput(adaptor);
      //thresholder->ThresholdAbove(th);
      //thresholder->SetOutsideValue(th);
      //duplicator->SetInputImage(thresholder->GetOutput());

      duplicator->SetInputImage(adaptor);
      duplicator->Modified();
      duplicator->Update();

      //cout << duplicator->GetOutput()->GetLargestPossibleRegion() << endl;
      //cout << "component: " << componentIndex << endl;
      //PrintImage<AdaptorType>(duplicator->GetOutput());

      composer->SetInput(componentIndex, duplicator->GetOutput());
      //composer->SetInput(componentIndex, adaptor);
      composer->Modified();
      composer->Update();
  }

  cout << "Output:" << endl;
  VectorImageType::Pointer imageout = composer->GetOutput();
  PrintImage<VectorImageType>(imageout); // Values are not good

  return EXIT_SUCCESS;
}
 
