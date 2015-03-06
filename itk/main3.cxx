#include "itkVectorImage.h"
#include "itkImageRegionIterator.h"
#include "itkThresholdImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
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
      cout << "image[" << ix << "," << iy << "] = " << ImageIt.Get() << endl;
  }
}
 
int main()
{
  VectorImageType::Pointer image = VectorImageType::New();
  CreateImage(image);

  cout << "Input:" << endl;
  PrintImage<VectorImageType>(image);

  // indexer
  typedef itk::VectorIndexSelectionCastImageFilter<VectorImageType, ScalarImageType> IndexerType;
  IndexerType::Pointer indexer = IndexerType::New();
  indexer->SetInput(image);
 
  // thresholder
  typedef itk::ThresholdImageFilter<ScalarImageType> ThresholderType;
  typename ThresholderType::Pointer thresholder = ThresholderType::New();
  PixelType th = 10;
  thresholder->ThresholdBelow(th);
  thresholder->SetOutsideValue(th);

  // Duplicator.
  typedef itk::ImageDuplicator<ScalarImageType> DuplicatorType;
  typename DuplicatorType::Pointer duplicator = DuplicatorType::New();

  // composer
  typedef itk::ComposeImageFilter<ScalarImageType> ComposerType;
  typename ComposerType::Pointer composer = ComposerType::New();
  

  for (unsigned int componentIndex = 0 ;
                    componentIndex < NumberOfComponents ; 
                    componentIndex++)
  {
      indexer->SetIndex(componentIndex);

      thresholder->SetInput(indexer->GetOutput());
      thresholder->Update();

      duplicator->SetInputImage(thresholder->GetOutput());
      duplicator->Update();

      composer->SetInput(componentIndex, duplicator->GetOutput());
      composer->Update();
  }

  cout << "Output:" << endl;
  PrintImage<VectorImageType>(composer->GetOutput());

  return EXIT_SUCCESS;
}
 
