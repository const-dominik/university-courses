SELECT DISTINCT City
FROM SalesLT.Address, SalesLT.SalesOrderHeader
WHERE SalesLT.Address.AddressID=SalesLT.SalesOrderHeader.ShipToAddressID
-- Assuming SalesOrderHeader.Status == 5 means it's delivered
-- If SalesOrderHeader contains only delivered orders, this condition is unnecesarry
AND SalesLT.SalesOrderHeader.Status = 5
ORDER BY City Desc