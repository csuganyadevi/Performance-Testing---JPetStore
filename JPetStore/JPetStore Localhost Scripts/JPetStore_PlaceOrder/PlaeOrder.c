PlaeOrder()
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

lr_start_transaction("JPetStore_PlaceOrder_T03_Selectcategory");
	
	web_url("sm_category.gif", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewCategory=&categoryId={rCategory}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 
		LAST);
		
		lr_end_transaction("JPetStore_PlaceOrder_T03_Selectcategory", LR_AUTO);


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
	
	lr_start_transaction("JPetStore_PlaceOrder_T04_SelectProduct");


	web_url("Catalog.action_2", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewProduct=&productId={rProductID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Catalog.action?viewCategory=&categoryId=FISH", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_PlaceOrder_T04_SelectProduct", LR_AUTO);


	/* ItemID */

	lr_think_time(10);
	
//	ItemID
	
	sItemID = lr_paramarr_random("ItemID");
	
	lr_save_string(sItemID, "rItemID");
	
	lr_start_transaction("JPetStore_PlaceOrder_T05_ViewItem");


	web_url("Catalog.action_3", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action?viewItem=&itemId={rItemID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://localhost:8080/jpetstore/actions/Catalog.action?viewProduct=&productId=FI-FW-02", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_PlaceOrder_T05_ViewItem", LR_AUTO);


	/* Addtocart */
	
	lr_think_time(10);
	
	lr_start_transaction("JPetStore_PlaceOrder_T06_AddtoCart");



	web_url("Cart.action", 
		"URL=http://localhost:8080/jpetstore/actions/Cart.action?addItemToCart=&workingItemId={rItemID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Catalog.action?viewItem=&itemId={rItemID}", 
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_PlaceOrder_T06_AddtoCart", LR_AUTO);



	/* checkout */
	
	lr_start_transaction("JPetStore_PlaceOrder_T07_checkout");


	web_url("Order.action", 
		"URL=http://localhost:8080/jpetstore/actions/Order.action?newOrderForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Cart.action?addItemToCart=&workingItemId={rItemID}", 
		"Snapshot=t94.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JPetStore_PlaceOrder_T07_checkout", LR_AUTO);


//	web_add_header("Origin", 
//		"https://petstore.octoperf.com");

	lr_think_time(10);
	
	generate_random_15_digit();
	
	lr_save_datetime("%m/%d", DATE_NOW + (ONE_DAY * 99), "ExpiryDate");
	
	lr_start_transaction("JPetStore_PlaceOrder_T08_PaymentDetails");


	web_submit_data("Order.action_2", 
		"Action=http://localhost:8080/jpetstore/actions/Order.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Order.action?newOrderForm=", 
		"Snapshot=t95.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=order.cardType", "Value=Visa", ENDITEM, 
		"Name=order.creditCard", "Value={CreditCard}", ENDITEM, 
		"Name=order.expiryDate", "Value={ExpiryDate}", ENDITEM, 
		"Name=order.billToFirstName", "Value={FirstName}", ENDITEM, 
		"Name=order.billToLastName", "Value={LastName}", ENDITEM, 
		"Name=order.billAddress1", "Value=billAddress1", ENDITEM, 
		"Name=order.billAddress2", "Value=billAddress2", ENDITEM, 
		"Name=order.billCity", "Value=billCity", ENDITEM, 
		"Name=order.billState", "Value=CA", ENDITEM, 
		"Name=order.billZip", "Value={ZIP}", ENDITEM, 
		"Name=order.billCountry", "Value=USA", ENDITEM, 
		"Name=newOrder", "Value=Continue", ENDITEM, 
//		"Name=_sourcePage", "Value=hrwYJRfKkZ7UzMfwWCxGoE3Hw4ES0gvganpIrBkkJhVlf7MNpBqsaeNClSh2vN0ayr5m1mzulW0qeu0p_b2oKENw1bY49LWnHe6cYa-r5G4=", ENDITEM, 
//		"Name=__fp", "Value=aDG5ISYkuHSt-E15KdhMIqQyNh8BTwiI33Bglc7qZn_Nw1JuL2CYd-Xi9L5U13QWGXu4YRGpTie-gJlJOTGz1Dj0RwcotMo9VRScWMdJqU-8InQ-Rf92cQ==", ENDITEM, 
		LAST);
	
	lr_end_transaction("JPetStore_PlaceOrder_T08_PaymentDetails", LR_AUTO);


	/* confirm page */

	lr_think_time(10);
	
	lr_start_transaction("JPetStore_PlaceOrder_T09_PlaceOrder");


	web_reg_find("Search=All",
		"SaveCount=OrderConfirm",
		"Text=Thank you",
		LAST);

	web_url("Confirm", 
		"URL=http://localhost:8080/jpetstore/actions/Order.action?newOrder=&confirmed=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Order.action", 
		"Snapshot=t96.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{OrderConfirm}")) >0)
	{
		lr_end_transaction("JPetStore_PlaceOrder_T09_PlaceOrder", LR_AUTO);
	}
else 
{
	lr_end_transaction("JPetStore_PlaceOrder_T09_PlaceOrder", LR_FAIL);
	lr_output_message("Order confirmation failed for Vuser_%d, Itr_No_%d", atoi(lr_eval_string("{VuserID}")),atoi(lr_eval_string("{Itr_No}")));
	
}



lr_think_time(10);

web_url("Return to Main Menu", 
		"URL=http://localhost:8080/jpetstore/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:8080/jpetstore/actions/Order.action?newOrder=&confirmed=true", 
		"Snapshot=t115.inf", 
		"Mode=HTML", 
		LAST);

lr_think_time(10);

	return 0;
}