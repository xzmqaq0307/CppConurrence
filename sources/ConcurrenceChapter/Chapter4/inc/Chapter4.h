#ifndef CHAPTER_4_H
#define CHAPTER_4_H

#if defined(CHAPTER_4_LIB)
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllexport)
#else
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllimport)
#endif



#endif