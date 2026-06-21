Login()
{
 

	web_cache_cleanup();
	
	web_cleanup_cookies();
	
//	web_set_sockets_option("SSL_VERSION", "AUTO");
 
//	JSESSIONID=C62D41F690CFF3D1FD89A14DB16878F5;
	
	web_reg_save_param_ex(
		"ParamName=SessionID",
		"LB=JSESSIONID=",
		"RB=;",
		SEARCH_FILTERS,
		LAST);
	
//	http://localhost:8080/jpetstore/actions/Catalog.action

//https://petstore.octoperf.com/actions/Catalog.action

	
   lr_start_transaction("JPetStore_Login_T01_Launch");
	
	web_url("Catalog.action", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t57.inf", 
		"Mode=HTML", 
		LAST);
  	 
  	lr_end_transaction("JPetStore_Login_T01_Launch", LR_AUTO);

    lr_think_time(10);
    
	/* LOGIN */
	
	web_reg_save_param_ex(
		"ParamName=Category",
		"LB=viewCategory=&amp;categoryId=",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);

	
	lr_start_transaction("JPetStore_Login_T02_Login");
	
	

	web_reg_find(
		//"Fail=Found",
		"Search=All",
		"SaveCount=SignIn_Fail",
		"Text=Signon failed",
		LAST);
	
//	http://localhost:8080/jpetstore/actions/Catalog.action

	web_submit_data("Account.action", 
		"Action=http://localhost:8080/jpetstore/actions/Account.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Account.action;jsessionid={SessionID}?signonForm=", 
		"Snapshot=t76.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={UserID}", ENDITEM, 
		"Name=password", "Value={UserID}", ENDITEM, 
		"Name=signon", "Value=Login", ENDITEM, 
		//"Name=_sourcePage", "Value=TptdGMhaMTC1Tx_Pune26BDBLnE2qLWexezuceW9c5v9HV935exdv7SUGs2AmJatxwDfLWdREX9qQws00tqYH-qO9i-66MFrfPV1OWyJ_WI=", ENDITEM, 
		//"Name=__fp", "Value=UU9V79spKxlAKuIzpMlDtOI1pckJpiqt-FEiGqnNTr9sa3dtTAUzVL7mWYszK6vs", ENDITEM, 
			LAST);
			
	if (atoi(lr_eval_string("{SignIn_Fail}")) == 0 )
	{
			
	lr_end_transaction("JPetStore_Login_T02_Login", LR_AUTO);
	
	}
	
	else
	{
		lr_end_transaction("JPetStore_Login_T02_Login", LR_FAIL);
		lr_output_message("The JPetStore Signon failed for : VuserID_%d , Itr_No_%d", atoi(lr_eval_string("{VuserID}")),atoi(lr_eval_string("{Itr_No}")));
		lr_abort();
	}

	
	lr_think_time(10);
	
	/* Signout */
		
		lr_start_transaction("JPetStore_Login_T03_Signout");


	web_url("Account.action_3", 
		"URL=http://localhost:8080/jpetstore/actions/Account.action?signoff=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Order.action?newOrder=&confirmed=true", 
		"Snapshot=t99.inf", 
		"Mode=HTML", 
		LAST);
		
		lr_end_transaction("JPetStore_Login_T03_Signout", LR_AUTO);

	

	
	



	return 0;
}