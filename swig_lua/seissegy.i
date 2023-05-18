%module seissegy
%{
#include "SeisISegy.h"
#include "SeisCommonSegy.h"
#include "SeisTrace.h"
%}

%include "SeisISegy.h"
%include "SeisCommonSegy.h"
%include "SeisTrace.h"

%include "carrays.i"
%array_functions(double, doubleArray);
