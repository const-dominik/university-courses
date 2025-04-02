SELECT SalesLT.ProductCategory.Name, SalesLT.Product.Name
FROM SalesLT.Product
LEFT JOIN SalesLT.ProductCategory on SalesLT.ProductCategory.ProductCategoryID = SalesLT.Product.ProductCategoryID
WHERE SalesLT.Product.ProductCategoryID 
IN (SELECT SalesLT.ProductCategory.ParentProductCategoryID FROM SalesLT.ProductCategory)
