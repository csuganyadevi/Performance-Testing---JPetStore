Browseategories()
{
 

/* Select category */

	web_reg_save_param_ex(
		"ParamName=ProductID",
		"LB=viewProduct=&amp;productId=",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);


//Category

sCategory = lr_paramarr_random("Category");

 lr_save_string(sCategory, "rCategory");

lr_start_transaction("JPetStore_Browsecategories_T02_Selectcategory");
	
	web_url("Catalog.action;jsessionid={SessionID}", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action;jsessionid={SessionID}?viewCategory=&categoryId={rCategory}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);
	
		lr_end_transaction("JPetStore_Browsecategories_T02_Selectcategory", LR_AUTO);


	/* Select Product */

	lr_think_time(10);
	
	/*web_reg_save_param_ex(
		"ParamName=ItemID",
		"LB=viewItem=&amp;itemId=",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
*/
	//	ProductID
		
		sProductID = lr_paramarr_random("ProductID");
	
//	lr_save_string("sProductID", "rProductID");
		
//		lr_param_sprintf("rProductID","%s",sProductID);   
		
		lr_param_sprintf("rProductID",sProductID);
	
	lr_start_transaction("JPetStore_Browsecategories_T03_SelectProduct");


	web_reg_find("Search=All",
		"SaveCount=SelectProduct",
		"Text=Add to Cart",
		LAST);

web_url("Catalog.action_2", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewProduct=&productId={rProductID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Catalog.action;jsessionid={SessionID}?viewCategory=&categoryId={rCategory}", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);
	
//	lr_end_transaction("JPetStore_Browsecategories_T03_SelectProduct", LR_AUTO);




//	lr_think_time(10);
	
	
	if (atoi(lr_eval_string("{SelectProduct}")) >0)
	{
		lr_end_transaction("JPetStore_Browsecategories_T03_SelectProduct", LR_AUTO);
	}
else 
{
	lr_end_transaction("JPetStore_Browsecategories_T03_SelectProduct", LR_FAIL);
	lr_output_message("Search Product failed for Vuser_%d, Itr_No_%d", atoi(lr_eval_string("{VuserID}")),atoi(lr_eval_string("{Itr_No}")));
	
}



lr_think_time(10);


	return 0;
}