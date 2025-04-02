SELECT pm.Name, Count(*)
FROM SalesLT.Product as p, SalesLT.ProductModel as pm
WHERE p.ProductModelID = pm.ProductModelID
GROUP BY pm.ProductModelID, pm.Name
HAVING COUNT(*) > 1