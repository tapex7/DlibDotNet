#ifndef _CPP_RANDOM_CROPPER_H_
#define _CPP_RANDOM_CROPPER_H_

#include "../export.h"
#include <dlib/image_transforms/random_cropper.h>
#include "../shared.h"

using namespace dlib;
using namespace std;


#pragma region template

#define ELEMENT element
#undef ELEMENT

#define random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects) \
do {\
    random_cropper& c = *cropper;\
    std::vector<matrix<ELEMENT>> tmp_images;\
    std::vector<std::vector<mmod_rect>> tmp_rects;\
    std::vector<matrix<ELEMENT>*>& in_images = *(static_cast<std::vector<matrix<ELEMENT>*>*>(images));\
    std::vector<std::vector<mmod_rect*>*>& in_rects = *(static_cast<std::vector<std::vector<mmod_rect*>*>*>(rects));\
    std::vector<matrix<ELEMENT>> tmp_ret_images;\
    std::vector<std::vector<mmod_rect>> tmp_ret_rects;\
    std::vector<matrix<ELEMENT>*>& out_images = *(static_cast<std::vector<matrix<ELEMENT>*>*>(crops));\
    std::vector<std::vector<mmod_rect*>*>& out_rects = *(static_cast<std::vector<std::vector<mmod_rect*>*>*>(crop_rects));\
    for (int j = 0; j < in_images.size(); j++)\
    {\
        matrix<ELEMENT>& m = *(in_images[j]);\
        tmp_images.push_back(m);\
        std::vector<mmod_rect*>& v = *(in_rects[j]);\
        std::vector<mmod_rect> tmp_v;\
        for (int i = 0; i < v.size(); i++)\
        {\
            mmod_rect& r = *(v[i]);\
            tmp_v.push_back(r);\
        }\
        tmp_rects.push_back(tmp_v);\
    }\
    c(num_crops, tmp_images, tmp_rects, tmp_ret_images, tmp_ret_rects);\
    for (int j = 0; j < tmp_ret_images.size(); j++)\
    {\
        matrix<ELEMENT>& m = tmp_ret_images[j];\
        out_images.push_back(new matrix<ELEMENT>(m));\
        std::vector<mmod_rect>& v = tmp_ret_rects[j];\
        std::vector<mmod_rect*>* tmp_v = new std::vector<mmod_rect*>();\
        for (int i = 0; i < v.size(); i++)\
        {\
            mmod_rect& r = v[i];\
            tmp_v->push_back(new mmod_rect(r));\
        }\
        out_rects.push_back(tmp_v);\
    }\
} while (0)

#pragma endregion template

DLLEXPORT random_cropper* random_cropper_new()
{
    return new random_cropper();
}

DLLEXPORT bool random_cropper_get_chip_dims(random_cropper* cropper, chip_dims** value)
{
    const chip_dims& dims = cropper->get_chip_dims();
    *value = new chip_dims(dims);
    return true;
}

DLLEXPORT bool random_cropper_get_background_crops_fraction(random_cropper* cropper, double* value) 
{
    *value = cropper->get_background_crops_fraction();
    return true;
}

DLLEXPORT bool random_cropper_get_max_object_size(random_cropper* cropper, double* value)
{
    *value = cropper->get_max_object_size();
    return true;
}

DLLEXPORT bool random_cropper_get_min_object_length_long_dim(random_cropper* cropper, long* value) 
{
    *value = cropper->get_min_object_length_long_dim();
    return true;
}

DLLEXPORT bool random_cropper_get_min_object_length_short_dim(random_cropper* cropper, long* value) 
{
    *value = cropper->get_min_object_length_short_dim();
    return true;
}

DLLEXPORT bool random_cropper_get_randomly_flip(random_cropper* cropper, bool* value) 
{
    *value = cropper->get_randomly_flip();
    return true;
}

DLLEXPORT bool random_cropper_get_max_rotation_degrees(random_cropper* cropper, double* value) 
{
    *value = cropper->get_max_rotation_degrees();
    return true;
}

DLLEXPORT bool random_cropper_get_translate_amount(random_cropper* cropper, double* value) 
{
    *value = cropper->get_translate_amount();
    return true;
}

DLLEXPORT void random_cropper_set_chip_dims(random_cropper* cropper, unsigned long rows, unsigned long cols)
{
    cropper->set_chip_dims(rows, cols);
}

DLLEXPORT void random_cropper_set_max_object_size(random_cropper* cropper, double value)
{
    cropper->set_max_object_size(value);
}

DLLEXPORT void random_cropper_set_min_object_size(random_cropper* cropper, long long_dim, long short_dim) 
{
    cropper->set_min_object_size(long_dim, short_dim);
}

DLLEXPORT void random_cropper_set_randomly_flip(random_cropper* cropper, bool value) 
{
    cropper->set_randomly_flip(value);
}

DLLEXPORT void random_cropper_set_max_rotation_degrees(random_cropper* cropper, double value) 
{
    cropper->set_max_rotation_degrees(value);
}

DLLEXPORT void random_cropper_set_background_crops_fraction(random_cropper* cropper, double value) 
{
    cropper->set_background_crops_fraction(value);
}

DLLEXPORT void random_cropper_set_translate_amount(random_cropper* cropper, double value) 
{
    cropper->set_translate_amount(value);
}

DLLEXPORT int random_cropper_operator(
    random_cropper* cropper, 
    size_t num_crops,
    matrix_element_type type,
    void* images,
    void* rects,
    void* crops,
    void* crop_rects)
{
    int err = ERR_OK;

    switch(type)
    {
        case matrix_element_type::UInt8:
            #define ELEMENT uint8_t
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT        
            break;
        case matrix_element_type::UInt16:
            #define ELEMENT uint16_t
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::UInt32:
            #define ELEMENT uint32_t
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::Int8:
            #define ELEMENT int8_t
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT        
            break;
        case matrix_element_type::Int16:
            #define ELEMENT int16_t
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::Int32:
            #define ELEMENT int32_t
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::Float:
            #define ELEMENT float
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::Double:
            #define ELEMENT double
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::RgbPixel:
            #define ELEMENT rgb_pixel
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::HsiPixel:
            #define ELEMENT hsi_pixel
            random_cropper_operator_template(cropper, num_crops, type, images, rects, crops, crop_rects);
            #undef ELEMENT
            break;
        case matrix_element_type::RgbAlphaPixel:
        default:
            err = ERR_ELEMENT_TYPE_NOT_SUPPORT;
            break;
    }
    
    return err;
}

DLLEXPORT void random_cropper_predictor_delete(random_cropper* obj)
{
	delete obj;
}

#endif