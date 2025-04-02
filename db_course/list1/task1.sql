SELECT DISTINCT City
FROM SalesLT.Address, SalesLT.SalesOrderHeader
WHERE SalesLT.Address.AddressID=SalesLT.SalesOrderHeader.ShipToAddressID
AND SalesLT.SalesOrderHeader.Status = 5
ORDER BY City Desc