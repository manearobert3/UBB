Use Test 
Go
Drop Table canSupply
Drop Table CleanerWorksOn
Drop Table CookWorksOn
Drop Table WaiterWorksOn
Drop Table Waiter
Drop Table RestaurantChain
Drop Table Cleaner
Drop Table HelperChef
Drop Table Cook
Drop Table Supplier
Drop Table Ingredient
Drop Table Recipe
GO
CREATE TABLE Waiter
	(WaiterID INT PRIMARY KEY,
	WName VARCHAR(50),
	FirstName VARCHAR(50),
	LastName VARCHAR(50),
	WShift VARCHAR(50))


Create table Cook
	(CookID INT Primary key,
	FirstName Varchar(50),
	LastName Varchar(50),
	Specialization Varchar(50))


Create table Recipe
	(RecipeID INT Primary key,
	RecipeName Varchar(50),
	Calories INT,
	Fats INT,
	Price INT)

CREATE TABLE Cleaner
	(CleanerID INT PRIMARY KEY,
	FirstName VARCHAR(50),
	LastName VarChar(50),
	CleanerScheduleDaysPerWeek INT)

Create Table RestaurantChain
	(RestaurantID INT Primary Key,
	RestaurantName Varchar(50),
	Adress VArchar(50),
	Phone VarCHar(50),
	MichelinStars INT)


Create table Ingredient
	(IngredientID INT Primary Key,
	RecipeID Int References Recipe(RecipeID),
	IngredientName VarChar(50),
	Quantity INT)

Create Table Supplier
	(SupplierID INT Primary Key,
	IngredientID INT References Ingredient(IngredientID),
	SupplierAdress VARCHAR(100),
	Price int)

Create table HelperChef
	(HelperChefID INT primary key,
	CookID INT References Cook(CookID),
	FirstName VarCHar(50),
	LastName VarChar(50),
	Experience INT)

Create Table CleanerWorksOn
	(CleanerID INT References Cleaner(CleanerID),
	RestaurantID INT References RestaurantChain(RestaurantID),
	Constraint PK_CleanerWorksOn Primary Key (CleanerID, RestaurantID))

Create Table CookWorksOn
	(RestaurantID INT References RestaurantChain(RestaurantID),
	CookID INt references Cook(CookID),
	Constraint PK_CookWorksOn Primary KEy(RestaurantID, CookID))

Create Table WaiterWorksOn
	(RestaurantID Int references RestaurantChain(RestaurantID),
	WaiterID INT References Waiter(WaiterID),
	Constraint PK_WaiterWorksON Primary KEy(RestaurantID,WaiterID))

Create Table canSupply
	(RestaurantID Int references RestaurantChain(RestaurantID),
	SupplierID INt references Supplier(SupplierID),
	Constraint PK_CanSupply Primary Key(RestaurantID,SupplierID))