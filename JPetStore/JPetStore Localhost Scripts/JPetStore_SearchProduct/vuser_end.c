vuser_end()
{
		/* Signout */
		
		lr_start_transaction("JPetStore_SearchProduct_T06_Signout");


	web_url("Account.action_3", 
		"URL=http://localhost:8080/jpetstore/actions/Account.action?signoff=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Order.action?newOrder=&confirmed=true", 
		"Snapshot=t99.inf", 
		"Mode=HTML", 
		LAST);
		
		lr_end_transaction("JPetStore_SearchProduct_T06_Signout", LR_AUTO);

	
	return 0;
}
