#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#define VERBOSE_

typedef enum
{
	kErrorCode_Ok = 0,
	kErrorCode_Memory = -1,
	kErrorCode_File = -2,
	kErrorCode_Null = -3,
	kErrorCode_Empty = -4,
	kErrorCode_Full = -5,
	kErrorCode_OutOfIndex = -6

} ErrorCode;

#endif // __COMMON_DEF_H__