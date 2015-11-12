#ifndef PARAMETER_H
#define PARAMETER_H


#include "ch.h"


#define PARAMETER_MAX_NAME			32
#define PARAMETER_MAX_STRING		255
#define PARAMETER_FLOAT_PRECISION	3


typedef enum {
	Int,
	Float,
	String
} parameterType;

typedef union {
	int				Int;
	float			Float;
	char*			String;
} parameterUnion;

typedef struct {
	parameterType	type;
	parameterUnion	val;
} parameter;


#ifdef __cplusplus
extern "C" {
#endif

	void				parameterInit(void);
	bool				parameterSearch( const char* name );
	parameter			parameterGet( const char* name );
	void				parameterSet( const char* name, const parameter value );

#ifdef __cplusplus
}
#endif


#endif // PARAMETER_H
