%skeleton "lalr1.cc"
%language "c++"
%code requires
{
    enum class IDType
    {
        Unknown,
        Function,
        Param,
        Variable
    }
    #include <map>
    #include <list>
    #include <vector>
    #include <string>
    #include <iostream>
    #include <algorithm>
    #include <cstdint>

    struct Identifier
    {
        id_type type = IDType::Unknown;
        size_t idx = 0;
        std::string name;    
    }
    struct Expression
    {
        expr_type type;
        identifier ident;
        std::string str;

        std::list<struct Expression> param_list; 
    }
}

%code
{

}
/*
%union{
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    float f32;
    float f64;
    std::string* str;
}
*/
%token EOF 0
%token MODULE "module" RETURN "return"  PRINT "print" WHILE "while" FOR "for" IF "if"  STRING_LITERAL NUMERIC_LITERAL IDENTIFIER
%token UINT8 "UInt8" UINT16 "UInt16" UINT32 "UInt32" UINT64 "UInt64" INT8 "Int8" INT16 "Int16" INT32 "Int32" INT64 "Int64" F32 "F32" F64 "F64" STRING "string"
%token OR "||" AND "&&" EQ "==" NE "!=" INC "++" DEC "--" PL_EQ "+=" MI_EQ "-=" ST_EQ "*=" SL_EQ "/=" PE_EQ "%="
%left ','
%right '=' "+=" "-=" "*=" "/=" "%=" "&=" "|=" "^=" 
%left "||"
%left "&&"
%left '|'
%left '^'
%left '&'
%left "==" "!="
%left '>' ">=" '<' "<="
%left '+' '-'
%left '*' '/' '%'
%right "++" "--" '!' '~'
%left '('
%%

module: MODULE IDENTIFIER '{' function '}';


statement: complex_statment '}'
|"return" expr ';'
| var_defs ';'
| "if" '(' expr ')' '{' statement '}'
| "while" '(' expr ')' '{' statement '}'
| "for" '(' var_def1 ';' expr ';' expr ')' '{' statement '}'
| "print" '(' expr ')' ';' 
| expr ';'
| ';'
;
complex_statment: '{'
| complex_statment statement;

function: "func" IDENTIFIER '(' func_args ')' '{' statement '}'
| %empty;

func_args: func_arg | %empty/* empty */;
func_arg: func_arg ','  typed_identifier | typed_identifier;

var_defs: "var" | var_def1
| var_defs ',' var_def1;
var_def1: typed_identifier '=' expr
| typed_identifier;
typed_identifier: type IDENTIFIER;



type: UINT8 
|     UINT16
|     UINT32
|     UINT64
|     INT8
|     INT16
|     INT32
|     INT64
|     F32
|     F64
|     STRING
;
expr: NUMERIC_LITERAL
|     STRING_LITERAL
|     IDENTIFIER
|     '(' expr ')' 
|      expr '(' expr ')'
|      expr '(' ')'
|      expr '=' expr
|      expr '+' expr
|      expr '-' expr %prec '+'
|      expr '*' expr
|      expr '/' expr
|      expr '%' expr
|      expr "+=" expr
|      expr "-=" expr
|      expr "&=" expr
|      expr "|=" expr
|      expr "^=" expr
|      expr "*=" expr
|      expr "/=" expr
|      expr "%=" expr
|      expr "==" expr
|      expr "!=" expr
|      expr '<' expr
|      expr "<=" expr
|      expr '>' expr
|      expr ">=" expr
|      expr "||" expr
|      expr "&&" expr
|      expr '|' expr
|      expr '&' expr
|      expr '^' expr
|      '-' expr %prec '~'
|      '+' expr %prec '~'
|      '!' expr %prec '~'
|      '~' expr 
|      "++" expr
|      "--" expr %prec "++"
|      expr "++"
|      expr "--" %prec "++"
| %empty/* empty */ ;
%%
