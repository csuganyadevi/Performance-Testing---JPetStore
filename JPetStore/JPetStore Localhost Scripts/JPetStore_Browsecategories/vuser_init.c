vuser_init()
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
	
	
		web_reg_save_param_ex(
		"ParamName=Category",
		"LB=viewCategory=&amp;categoryId=",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
	
   lr_start_transaction("JPetStore_Browsecategories_T01_Launch");
	
	web_reg_find("Search=All",
		"SaveCount=Welcome_count",
		"Text=Welcome",
		LAST);

	web_url("Catalog.action", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t57.inf", 
		"Mode=HTML", 
		LAST);
  	 
//  	lr_end_transaction("JPetStore_Browsecategories_T01_Launch", LR_AUTO);

	
		
	if (atoi(lr_eval_string("{Welcome_count}")) > 0 )
	{
			
	lr_end_transaction("JPetStore_Browsecategories_T01_Launch", LR_AUTO);
	
	}
	
	else
	{
		lr_end_transaction("JPetStore_Browsecategories_T01_Launch", LR_FAIL);
		lr_output_message("The JPetStore Launch failed for : VuserID_%d , Itr_No_%d", atoi(lr_eval_string("{VuserID}")),atoi(lr_eval_string("{Itr_No}")));
		lr_abort();
	}

	
	lr_think_time(10);

	
	

	
	return 0;
}
