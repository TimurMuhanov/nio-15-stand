#ifndef PARAMETER_H
#define PARAMETER_H


#include "ch.h"


#define PARAMETER_MAX_RECORD_LENGTH	255
#define PARAMETER_MAX_STRING_LENGTH	255
#define PARAMETER_FLOAT_PRECISION	"3"


typedef enum {
	Int,
	Float,
	String
} ParameterType;

typedef struct {
	ParameterType	type;
	union {
		int		Int;
		float	Float;
		char*	String;
	}				val;
} Parameter;


#ifdef __cplusplus
extern "C" {
#endif

	void				parameterInit(void);
	Parameter*			parameterGet( const char* name );
	void				parameterAdd( const char* name, Parameter* parameter );
	void				parameterSync();

#ifdef __cplusplus
}
#endif


#endif // PARAMETER_H
