Use Test
Go

Select * from Tests
Select* from TestRunTables 
Select * from Tests;
Select * from Tables
delete from Tables
Insert Into Tables(Name)
Values('Cook'),('Recipe'),('Ingredient'),('MultiColumn')

Insert Into Tables(Name)
Values('RestaurantChain'),('WaiterWorksOn'),('Waiter');
INSERT INTO TestTables (TestID,TableID,NoOfRows,Position)
Values(1,4,5,4);
delete from TestRuns;

Select* from TestRuns
DBCC CHECKIDENT ('Tests', RESEED, 0);
DBCC CHECKIDENT ('Tables', RESEED, 0);
DBCC CHECKIDENT ('TestRuns', RESEED, 0);
Select* from TestTables
delete from TestTables
Insert INTO TestTables(TestID,TableID,NoOfRows,Position)
--Values(1,1,5,3),(1,2,5,2),(1,3,5,1);
Values(2,5,50,3),(2,7,50,2),(2,6,50,1)
Delete From Cook;
Delete from Recipe;
Select* from Cook
Select* from Recipe;
Select * from Ingredient
Select * from #TempTableIDs
Select* from RestaurantChain
Select* from WaiterWorksOn
Select* from Waiter


delete from TestRuns
Select* from TestRuns
Select* from TestRunTables

Insert Into TestRunTables (TestRunID,TableID,StartAt,EndAt)
Values (1,1,1,1);

Select * from Cook
Delete from HelperChef
Delete from Cook
Delete from Recipe
Delete from Ingredient
Delete from Supplier

EXEC InsertRandomDataWRT @TestID=2;
select* from TestRunViews

Insert INto Views (Name)
Values('oneTable'),('SelectOnTwoTables'),('IngredientSummary');

Insert Into TestViews(TestID,ViewID)
Values (1,1),(1,2),(1,3)
Select * from Views
Select * from TestViews
SELECT ViewID
		FROM TestViews
		WHERE TestID = 1;


create or alter view oneTable 
as 
 Select* from Cook
SELECT * FROM oneTable;

create or alter view SelectOnTwoTables
as 
Select IngredientID,Recipe.RecipeName
from Ingredient
inner join Recipe on Ingredient.RecipeID=Recipe.RecipeID;
SELECT * from SelectOnTwoTables
select* from Ingredient


CREATE VIEW IngredientSummary AS
SELECT
    I.IngredientName,
    SUM(I.Quantity) AS TotalQuantity,
    R.RecipeID,
    R.RecipeName
FROM
    Ingredient I
INNER JOIN
    Recipe R ON I.RecipeID = R.RecipeID
GROUP BY
    I.IngredientName, R.RecipeID, R.RecipeName;


	CREATE TABLE MultiColumn (
    ID INT,
    OrderInfo NVarChar(100),
    ProductName NVARCHAR(100),
    Quantity INT,
    PRIMARY KEY (ID, OrderInfo)
);