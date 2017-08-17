// MIG规格文件语法
specification file:
subsystem description,
waittime description option,
msgtype description option,
error description option,
server prefix description option,
user prefix description option,
rscid description option
type description sequence option,
import statement sequence option,
operation description sequence.
subsystem description:
"Subsystem", identifier, decimal integer, ";".
waittime description:
"WaitTime", waittime value, ";" |
"NoWaitTime",";".
waittime value:
decimal integer |
identifier.
msgtype description:
"MsgType", msgtype value, ";".
msgtype value:
"MSG_TYPE_RPC" |
"MSG_TYPE_ENCRYPTED" |
"MSG_TYPE_NORMAL" .
error description:
"Error", identifier, ";".
server prefix description:
"ServerPrefix", identifier ";".
user prefix description:
"UserPrefix", identifier, ";".
import statement:
import indicant, include name, ";".
include name:
"file_name"|
<file_name>.
import indicant:
"import"|
"uimport"|
"simport".
type description:
"type", type definition, ";".
operation description:
routine description |
simpleroutine description |
procedure description |
simpleprocedure description |
function description |
camelotroutine description.
routine description:
"routine", argument list, ";".
simpleroutine description:
"simpleroutine", argument list, ";".
procedure description:
"procedure", argument list, ";".
simpleprocedure description:
"simpleprocedure", argument list, ";".
function description:
"function", argument list, ":", type definition, ";".
camelotroutine description:
"routine", argument list, ";".
argument list:
"(", argument definition option,
semicolon joined argument definition sequence option, ")".
semicolon joined argument definition:
";", argument definition.
argument definition:
specification option, identifer, ":", type definition,
ipc flag sequence option.
specification:
"in" |
"out" |
"inout" |
"requestport" |
"replyport" |
"waittime" |
"msgtype".
type definition:
identifier, "=",
pointer option, repetition option sequence,
ipc_info, translation option.
pointer: "^".
repetition:
"array", "[", size option, "]", "of"|
"struct", "[", size option, "]", "of".
size: integer expression|
" * :", integer expression.
integer expression: integer expression, "+", integer expression |
integer expression, "-", integer expression |
integer expression, "*", integer expression |
integer expression, "/", integer expression |
"(", integer expression, ")" |
integer.
ipc_info:
"(", ipc_type_name, ",", size in bits,
ipc flag sequence option, ")" |
ipc_type_name |
identifier.
ipc_type_name:
prim_ipc_type_name |
prim_ipc_type_name, "|", prim_ipc_type_name.
prim_ipc_type_name:
"polymorphic" |
builtin type name |             /*参见附录4*/
integer expression.
translation:
ctype option, cusertype option, cservertype option,
input function option, output function option,
destructor function option.
ctype:
"CType", ":", identifier.
cusertype:
"CUserType", ":", identifier.
cservertype:
"CServerType", ":", identifier.
input function:
"InTran", ":", identifier, identifier, "(", indentifier, ")".
output function:
"OutTran", ":", identifier, identifier, "(", indentifier, ")".
destructor function:
"Destructor", ":", identifier, "(", indentifier, ")".
ipc flag:
",", flag identifier.
flag identifer:
"dealloc" |
"notdealloc" |
"islong" |
"isnotlong".
//附录4 系统定义的IPC类型
系统内置的IPC类型如下：
MSG_TYPE_UNSTRUCTURED
MSG_TYPE_BIT
MSG_TYPE_BOOLEAN
MSG_TYPE_INTEGER_16
MSG_TYPE_INTEGER_32
MSG_TYPE_PORT_OWNERSHIP
MSG_TYPE_PORT_RECEIVE
MSG_TYPE_PORT_ALL
MSG_TYPE_PORT
MSG_TYPE_CHAR
MSG_TYPE_BYTE
MSG_TYPE_INTEGER_8
MSG_TYPE_REAL
MSG_TYPE_STRING
MSG_TYPE_PORT_NAME
MSG_TYPE_INTERNAL_MEMORY
MSG_TYPE_POLYMORPHIC
最新的类型名称需要在<mach/message.h>中去寻找。
