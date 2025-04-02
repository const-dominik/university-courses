exec sp_help "SalesLT.SalesOrderHeader";

alter table SalesLT.SalesOrderHeader with nocheck
	add constraint CK_SalesOrderHeader_ShipDate 
		check (([ShipDate]>=[OrderDate] OR [ShipDate] IS NULL));