User_Registration()
{

	web_cache_cleanup();
	
	web_cleanup_cookies();
	
//	fName = "D:\\Suganya\\LR Sripts\\JPetStore_RegisterUsers\\userid_reg.txt";
	
	
	
	web_set_sockets_option("SSL_VERSION","AUTO");
	

	
	web_reg_save_param_ex("ParamName=SessionId",
	                      "LB=JSESSIONID=",
	                      "RB=;",
	                      LAST);
	
	lr_start_transaction("JPetStore_UserRegistration_T01_Launch");


	web_url("Catalog.action", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_UserRegistration_T01_Launch", LR_AUTO);


	//SignIn
	
	lr_think_time(10);
	
	lr_start_transaction("JPetStore_UserRegistration_T02_SignIn");


	web_url("Account.action;jsessionid={SessionId}", 
		"URL=http://localhost:8080/jpetstore/actions/Account.action;jsessionid={SessionId}?signonForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"Snapshot=t23.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_UserRegistration_T02_SignIn", LR_AUTO);

	
	//RegisterNow
	
	//<option value="BIRDS">BIRDS</option>
	
	/*web_reg_save_param_ex(
		"ParamName=Favourite",
		"LB=<option value=\"",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);*/
	
	
	lr_start_transaction("JPetStore_UserRegistration_T03_RegisterNow");

	
	web_url("Account.action", 
		"URL=http://localhost:8080/jpetstore/actions/Account.action?newAccountForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Account.action;jsessionid={SessionId}?signonForm=", 
		"Snapshot=t28.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_UserRegistration_T03_RegisterNow", LR_AUTO);


	//Save Account Information
	
	

	
	
	UserName = lr_eval_string("UserID{Timestamp}{VUserID}{Itr_No}");
	
//		UserName = lr_eval_string("UserIDV{VUserID}{Itr_No}");
	
	lr_output_message("The UserID is:%s",UserName);
		
	lr_save_string(UserName,"UserID");
	
	
	

	lr_start_transaction("JPetStore_UserRegistration_T04_SaveAccount");
	
	web_submit_data("Account.action_2", 
		"Action=http://localhost:8080/jpetstore/actions/Account.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Account.action?newAccountForm=", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={UserID}", ENDITEM, 
		"Name=password", "Value={UserID}", ENDITEM, 
		"Name=repeatedPassword", "Value={UserID}", ENDITEM, 
		"Name=account.firstName", "Value={UserID}", ENDITEM, 
		"Name=account.lastName", "Value={UserID}", ENDITEM, 
		"Name=account.email", "Value={UserID}", ENDITEM, 
		"Name=account.phone", "Value={Phone}", ENDITEM, 
		"Name=account.address1", "Value={UserID}", ENDITEM, 
		"Name=account.address2", "Value={UserID}", ENDITEM, 
		"Name=account.city", "Value={UserID}", ENDITEM, 
		"Name=account.state", "Value=Tamil Nadu", ENDITEM, 
		"Name=account.zip", "Value={ZIP}", ENDITEM, 
		"Name=account.country", "Value=India", ENDITEM, 
		"Name=account.languagePreference", "Value={Language}", ENDITEM, 
		"Name=account.favouriteCategoryId", "Value={Favourite}", ENDITEM, 
		"Name=newAccount", "Value=Save Account Information", ENDITEM, 
//		"Name=_sourcePage", "Value=_HGOJxBHSyImyELFZlPE2mZ9qYZRafHBmfySWBY7gyNWr5PcTuxusXfgAceFBAUQEIhgK6Z6ZjXZhtXezfd5yBAq5Qtt4BQIdV8DydIUTfA=", ENDITEM, 
//		"Name=__fp", "Value=jKDFg5QTIrWc2jXot_tpXUZGQ-q083oGz2a2MaSSDdaMe052FM7Vy841MX2ZIm2EUQn5UuGJjaJbM67dI0ETDEOI-RvhSd9by84hrL_lKqYFliD1kA4fF1mypziMPcLt8iUx5MfSnrMLQrZwq5iwG1m0XdHaikSQIs6qlEZIfl9WMVmzFBinkgubH1AZ3Hye", ENDITEM, 
		LAST);
	
	
	statuscode = web_get_int_property(HTTP_INFO_RETURN_CODE);
	
	if (statuscode == 500)
	{
	lr_end_transaction("JPetStore_UserRegistration_T04_SaveAccount",LR_FAIL);
	
	}
	else
	{
		
	lr_end_transaction("JPetStore_UserRegistration_T04_SaveAccount",LR_AUTO);
	fOut = fopen("D:\\Suganya\\LR Sripts\\JPetStore New Project\\JPetStore_RegisterUsers\\userid_reg.txt","a");
		
		if (fOut ==NULL)
	{
		return -1;
	}


	fprintf (fOut, "%s\n", UserName);
	fclose (fOut);
	
	}

	return 0;
}