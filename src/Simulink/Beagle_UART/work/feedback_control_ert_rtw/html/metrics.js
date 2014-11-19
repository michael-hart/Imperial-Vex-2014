function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["feedback_control_DWork"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	size: 16};
	 this.metricsArray.var["feedback_control_M_"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	size: 4};
	 this.metricsArray.var["feedback_control_P"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control_data.c",
	size: 32};
	 this.metricsArray.var["feedback_control_U"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	size: 8};
	 this.metricsArray.var["feedback_control_Y"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	size: 8};
	 this.metricsArray.fcn["feedback_control_initialize"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["feedback_control_step"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	stack: 8,
	stackTotal: 8};
	 this.metricsArray.fcn["feedback_control_terminate"] = {file: "F:\\VEX\\repo\\src\\Simulink\\Beagle_UART\\work\\feedback_control_ert_rtw\\feedback_control.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data;}
}
	 CodeMetrics.instance = new CodeMetrics();
