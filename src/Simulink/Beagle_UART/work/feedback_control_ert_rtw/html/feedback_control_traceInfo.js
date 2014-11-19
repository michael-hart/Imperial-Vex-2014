function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/u */
	this.urlHashMap["feedback_control:1"] = "feedback_control.c:40,50,59&feedback_control.h:42";
	/* <Root>/y */
	this.urlHashMap["feedback_control:2"] = "feedback_control.c:47&feedback_control.h:47";
	/* <S1>/Derivative Gain */
	this.urlHashMap["feedback_control:4:1668"] = "feedback_control.c:39&feedback_control.h:54&feedback_control_data.c:28";
	/* <S1>/Filter */
	this.urlHashMap["feedback_control:4:1670"] = "feedback_control.c:38,64&feedback_control.h:37";
	/* <S1>/Filter Coefficient */
	this.urlHashMap["feedback_control:4:1671"] = "feedback_control.c:37&feedback_control.h:55&feedback_control_data.c:29";
	/* <S1>/Integral Gain */
	this.urlHashMap["feedback_control:4:1667"] = "feedback_control.c:58&feedback_control.h:56&feedback_control_data.c:30";
	/* <S1>/Integrator */
	this.urlHashMap["feedback_control:4:1669"] = "feedback_control.c:48,57&feedback_control.h:36";
	/* <S1>/Proportional Gain */
	this.urlHashMap["feedback_control:4:1666"] = "feedback_control.c:49&feedback_control.h:57&feedback_control_data.c:31";
	/* <S1>/Sum */
	this.urlHashMap["feedback_control:4:1665"] = "feedback_control.c:51";
	/* <S1>/SumD */
	this.urlHashMap["feedback_control:4:1672"] = "feedback_control.c:41";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "feedback_control"};
	this.sidHashMap["feedback_control"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "feedback_control:4"};
	this.sidHashMap["feedback_control:4"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<Root>/u"] = {sid: "feedback_control:1"};
	this.sidHashMap["feedback_control:1"] = {rtwname: "<Root>/u"};
	this.rtwnameHashMap["<Root>/Discrete PID Controller"] = {sid: "feedback_control:4"};
	this.sidHashMap["feedback_control:4"] = {rtwname: "<Root>/Discrete PID Controller"};
	this.rtwnameHashMap["<Root>/y"] = {sid: "feedback_control:2"};
	this.sidHashMap["feedback_control:2"] = {rtwname: "<Root>/y"};
	this.rtwnameHashMap["<S1>/u"] = {sid: "feedback_control:4:1"};
	this.sidHashMap["feedback_control:4:1"] = {rtwname: "<S1>/u"};
	this.rtwnameHashMap["<S1>/Derivative Gain"] = {sid: "feedback_control:4:1668"};
	this.sidHashMap["feedback_control:4:1668"] = {rtwname: "<S1>/Derivative Gain"};
	this.rtwnameHashMap["<S1>/Filter"] = {sid: "feedback_control:4:1670"};
	this.sidHashMap["feedback_control:4:1670"] = {rtwname: "<S1>/Filter"};
	this.rtwnameHashMap["<S1>/Filter Coefficient"] = {sid: "feedback_control:4:1671"};
	this.sidHashMap["feedback_control:4:1671"] = {rtwname: "<S1>/Filter Coefficient"};
	this.rtwnameHashMap["<S1>/Integral Gain"] = {sid: "feedback_control:4:1667"};
	this.sidHashMap["feedback_control:4:1667"] = {rtwname: "<S1>/Integral Gain"};
	this.rtwnameHashMap["<S1>/Integrator"] = {sid: "feedback_control:4:1669"};
	this.sidHashMap["feedback_control:4:1669"] = {rtwname: "<S1>/Integrator"};
	this.rtwnameHashMap["<S1>/Proportional Gain"] = {sid: "feedback_control:4:1666"};
	this.sidHashMap["feedback_control:4:1666"] = {rtwname: "<S1>/Proportional Gain"};
	this.rtwnameHashMap["<S1>/Sum"] = {sid: "feedback_control:4:1665"};
	this.sidHashMap["feedback_control:4:1665"] = {rtwname: "<S1>/Sum"};
	this.rtwnameHashMap["<S1>/SumD"] = {sid: "feedback_control:4:1672"};
	this.sidHashMap["feedback_control:4:1672"] = {rtwname: "<S1>/SumD"};
	this.rtwnameHashMap["<S1>/y"] = {sid: "feedback_control:4:10"};
	this.sidHashMap["feedback_control:4:10"] = {rtwname: "<S1>/y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
