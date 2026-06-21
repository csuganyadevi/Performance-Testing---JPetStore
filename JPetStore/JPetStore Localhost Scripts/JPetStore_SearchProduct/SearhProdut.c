SearhProdut()
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

lr_start_transaction("JPetStore_SearchProduct_T03_Selectcategory");
	
	web_url("sm_category.gif", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewCategory=&categoryId={rCategory}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 
		LAST);
		
		lr_end_transaction("JPetStore_SearchProduct_T03_Selectcategory", LR_AUTO);


	/* Select Product */

	lr_think_time(10);
	
	web_reg_save_param_ex(
		"ParamName=ItemID",
		"LB=viewItem=&amp;itemId=",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);

	//	ProductID
		
		sProductID = lr_paramarr_random("ProductID");
	
//	lr_save_string("sProductID", "rProductID");
		
//		lr_param_sprintf("rProductID","%s",sProductID);   
		
		lr_param_sprintf("rProductID",sProductID);
	
	lr_start_transaction("JPetStore_SearchProduct_T04_SelectProduct");


	web_url("Catalog.action_2", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewProduct=&productId={rProductID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Catalog.action?viewCategory=&categoryId=FISH", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_SearchProduct_T04_SelectProduct", LR_AUTO);


	/* ItemID */

	lr_think_time(10);
	
//	ItemID
	
	sItemID = lr_paramarr_random("ItemID");
	
	lr_save_string(sItemID, "rItemID");
	
	lr_start_transaction("JPetStore_SearchProduct_T05_ViewItem");


	web_reg_find("Search=All",
		"SaveCount=Viewcount",
		"Text=Add to Cart",
		LAST);

	web_url("Catalog.action_3", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewItem=&itemId={rItemID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Catalog.action?viewProduct=&productId=FI-FW-02", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		LAST);
	
//	lr_end_transaction("JPetStore_SearchProduct_T05_ViewItem", LR_AUTO);


	
	if (atoi(lr_eval_string("{Viewcount}")) >0)
	{
		lr_end_transaction("JPetStore_SearchProduct_T05_ViewItem", LR_AUTO);
	}
else 
{
	lr_end_transaction("JPetStore_SearchProduct_T05_ViewItem", LR_FAIL);
	lr_output_message("ViewItem failed for Vuser_%d, Itr_No_%d", atoi(lr_eval_string("{VuserID}")),atoi(lr_eval_string("{Itr_No}")));
	
}



lr_think_time(10);


	return 0;
}