function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:33,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:70,type:"fcn"};
this.def["feedback_control_DWork"] = {file: "feedback_control_c.html",line:20,type:"var"};
this.def["feedback_control_U"] = {file: "feedback_control_c.html",line:23,type:"var"};
this.def["feedback_control_Y"] = {file: "feedback_control_c.html",line:26,type:"var"};
this.def["feedback_control_M_"] = {file: "feedback_control_c.html",line:29,type:"var"};
this.def["feedback_control_M"] = {file: "feedback_control_c.html",line:30,type:"var"};
this.def["feedback_control_step"] = {file: "feedback_control_c.html",line:33,type:"fcn"};
this.def["feedback_control_initialize"] = {file: "feedback_control_c.html",line:69,type:"fcn"};
this.def["feedback_control_terminate"] = {file: "feedback_control_c.html",line:75,type:"fcn"};
this.def["D_Work_feedback_control"] = {file: "feedback_control_h.html",line:38,type:"type"};
this.def["ExternalInputs_feedback_control"] = {file: "feedback_control_h.html",line:43,type:"type"};
this.def["ExternalOutputs_feedback_contro"] = {file: "feedback_control_h.html",line:48,type:"type"};
this.def["pid_param"] = {file: "feedback_control_types_h.html",line:27,type:"type"};
this.def["Parameters_feedback_control"] = {file: "feedback_control_types_h.html",line:32,type:"type"};
this.def["RT_MODEL_feedback_control"] = {file: "feedback_control_types_h.html",line:35,type:"type"};
this.def["feedback_control_P"] = {file: "feedback_control_data_c.html",line:20,type:"var"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:80,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:85,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:90,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:97,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:104,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:111,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:118,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:125,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:132,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:153,type:"type"};
this.def["ZCDirection"] = {file: "rtwtypes_h.html",line:164,type:"type"};
this.def["ZCSigState"] = {file: "rtwtypes_h.html",line:167,type:"type"};
this.def["ZCEventType"] = {file: "rtwtypes_h.html",line:180,type:"type"};
}
CodeDefine.instance = new CodeDefine();
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["feedback_control_c.html"] = "../feedback_control.c";
	this.html2Root["feedback_control_c.html"] = "feedback_control_c.html";
	this.html2SrcPath["feedback_control_h.html"] = "../feedback_control.h";
	this.html2Root["feedback_control_h.html"] = "feedback_control_h.html";
	this.html2SrcPath["feedback_control_private_h.html"] = "../feedback_control_private.h";
	this.html2Root["feedback_control_private_h.html"] = "feedback_control_private_h.html";
	this.html2SrcPath["feedback_control_types_h.html"] = "../feedback_control_types.h";
	this.html2Root["feedback_control_types_h.html"] = "feedback_control_types_h.html";
	this.html2SrcPath["feedback_control_data_c.html"] = "../feedback_control_data.c";
	this.html2Root["feedback_control_data_c.html"] = "feedback_control_data_c.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","feedback_control_c.html","feedback_control_h.html","feedback_control_private_h.html","feedback_control_types_h.html","feedback_control_data_c.html","rtwtypes_h.html"];
