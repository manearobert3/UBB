Use Test
Go

Insert Cook(CookID, FirstName, LastName, Specialization)
	Values (1,'Xavier','Barnes', 'Fish'),
	(2,'Celine','Layun', 'Fish'),
	(3,'Ion','Ionescu', 'Dessert')

Insert HelperChef(HelperChefID, CookID, FirstName, LastName, Experience)
	Values (101,1,'Remington','Garner',5),
	(102,NULL,'Garfield','Hauewi',3);

Insert Recipe(RecipeID,RecipeName,Calories,Fats,Price)
	Values(201,'Lo Mein Noodles',300,17,30),
	(202,'Vegetable Egg Roll',150,6,29),
	(203,'Shanghai Noodles',410,15,18),
	(204,'Honey Garlic Chicken',430,21,27),
	(205,'General Tso''s Chicken',360,21,38),
	(206,'Zoodles (Zucchini Noodles)',60,4.5,11),
	(207,'Cinnamon Bread Twists',250,12,14),
	(208,'Chicken Parm Sandwich',400,15,18),
	(209,'Chicken Carbonara in Dish',690,34,43),
	(210,'Chicken Caesar Salad',280,12,21),
	(211,'Chicken Shawarma Salad',380,15,28),
	(212,'ASDAASD',400,15,30),
	(213,'ASDAASD222',300,14,30),
	(214,'123124124',400,16,30)


Insert RestaurantChain(RestaurantID,RestaurantName,Adress,Phone,MichelinStars)
	Values(401,'Applebee''s','Georgia','+15207839727',0),
	(402,'Burger King','Miami','+17372221635',3),
	(403,'Chick-Fil-A','Georgia','+14196540175',0)


Insert Ingredient(IngredientID,RecipeID,IngredientName,Quantity)
	Values(23,210,'Sugar',120),
	(24,210,'Flour',300)

Insert Supplier(SupplierID,IngredientID,SupplierName,Price)
	Values(301,23,'Golden State Foods','Expensive'),
	(302,23,'Dot Transportation','Cheap'),
	(303,24,'Martin Brower','Expensive')

Insert canSupply(SupplierID,RestaurantID)
	Values(301,401),(302,402),(301,403)

Insert CookWorksOn(RestaurantID,CookID)
	Values(401,1),
	(402,2)

Insert Producer(ProducerID,EcoProducts,ExperienceInYears,ProducerName,ProducerAdress)	
	Values(801,2,6,'Green Acres Ranch','Texas'),
	(802,3,3,'Green Valley Farm','Missouri')

Insert GetsFromAProducer(SupplierID,ProducerID)
	Values(301,801),
	(302,801)

Insert Waiter(WaiterID,WShift,LastName,FirstName)
	Values (90,'Night','Andrei','Ion'),
	(91,'Day','Vasile','Ionut'),
	(92,'Night','Marcovei','Stefan')

insert WaiterWorksOn(RestaurantID,WaiterID)
	Values(401,92),(402,91)


Update Recipe
Set Price = '45'
Where Calories >= 420 Or Price >42

Update Recipe
Set Fats = '15'
Where RecipeID=203

Update Recipe
Set Calories = 400
Where RecipeID=203

Update HelperChef
Set Experience = 6
Where HelperChefID=101

Update Recipe
Set Price = '29'
Where RecipeID=211



Delete from Recipe where RecipeID='202'

Delete from Recipe where RecipeName='Lo Mein Noodles'

Delete from Recipe where RecipeName='Zoodles (Zucchini Noodles)'

DELETE FROM HelperChef
Where CookID IS NULL


UPDATE Recipe
SET Price = '35'
WHERE Calories BETWEEN 600 AND 700;

UPDATE Producer
SET EcoProducts =3
WHERE Producer.ProducerName LIKE '%Farm%';

SELECT *
FROM Recipe
SELECT *
FROM Cook
SELECT *
FROM HelperChef
Select*
From RestaurantChain
Select*
From Supplier
Select*
From Producer
Select*
From Waiter
Select* 
From Supplier




--a. 2 queries with the union operation; use UNION [ALL] and OR;
-- select top 3 restaurants in georgia and in miami that have a supplier
Select TOP(3) R.RestaurantName
From RestaurantChain R, canSupply cs, Supplier S
Where R.RestaurantID=cs.RestaurantID And s.SupplierID=cs.SupplierID And R.Adress='Georgia'
Union
Select TOP(3) R2.RestaurantName
From RestaurantChain R2, canSupply cs2, Supplier S2
Where R2.RestaurantID=cs2.RestaurantID And s2.SupplierID=cs2.SupplierID And R2.Adress='Miami'
		
--top 10 Suplier names that have price of expensive and moderate
Select TOP (10) S.SupplierName
From Supplier S
Where S.Price ='Expensive' OR S.Price = 'Moderate'

--b. 2 queries with the intersection operation; use INTERSECT and IN;

-- select the first name of the chef that has a specialization in 'Fish' and work in a restaurant
SELECT C.FirstName
FROM Cook C
WHERE C.CookID IN (
    SELECT DISTINCT C1.CookID
    FROM Cook C1
    WHERE C1.Specialization = 'Fish'
) INTERSECT
SELECT C2.FirstName
FROM Cook C2
WHERE C2.CookID IN (
    SELECT DISTINCT C3.CookID
    FROM Cook C3
    JOIN CookWorksOn CO ON C3.CookID=CO.CookID
)
-- select the recipe name of the recipe that is used by any ingredient
Select R.RecipeName
From Recipe R
Where R.RecipeID in ( select RecipeID from Ingredient)

--c. 2 queries with the difference operation; use EXCEPT and NOT IN;
-- select the producer's name that has no more then 2 eco products
select P.ProducerName
From Producer P
except
select P2.ProducerName
From Producer P2
where P2.EcoProducts>2


-- first and last name of cooks that don't have a helperChef
Select C.FirstName, C.LastName
From HelperChef HC, Cook C
Where C.CookID not in (Select CookID From HelperChef)

--d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator);
--one query will join at least 3 tables, while another one will join at least two many-to-many relationships;


--all HelperChefs and for each HelperChef show the matching Cook with specialization 'Fish', otherwise 'NULL'
Select HC.FirstName, HC.LastName, C.FirstName, C.LastName
From HelperChef HC
Left Join Cook C ON C.Specialization='Fish'


-- join at least two many-to-many relationships
--get the RestaurantName and Supplier price and Producer's Experience for the connected Restaurant-Supplier-Producer
-- and where the Restaurant's Michelin Stars are equal to 0, Supplier's Price ='Expensive' and Producer's Experience is >5
Select R.RestaurantName, S.Price, P.ExperienceInYears
From Supplier S inner join canSupply cs on s.SupplierID=cs.SupplierID
INNER JOIN RestaurantChain R on R.RestaurantID=cs.RestaurantID
Join GetsFromAProducer G ON S.SupplierID=G.SupplierID
Join Producer P ON P.ProducerID=G.ProducerID 
where MichelinStars=0 AND S.Price='Expensive' AND P.ExperienceInYears >5


-- return rows that have matching data in all the specified tables, 
-- combining the restaurant name, supplier name, and ingredient name where there are valid relationships
SELECT R.RestaurantName, S.SupplierName, I.IngredientName
FROM RestaurantChain R
inner join canSupply cs ON R.RestaurantID = cs.RestaurantID
inner join Supplier S ON S.SupplierID = cs.SupplierID
inner join Ingredient I ON I.IngredientID = S.IngredientID;

-- return all the restaurant's names and waiter's first and last name.
SELECT R.RestaurantName, W.FirstName,W.LastName
FROM RestaurantChain R
FULL JOIN WaiterWorksOn WW ON R.RestaurantID = WW.RestaurantID
FULL JOIN Waiter W ON W.WaiterID = WW.WaiterID


-- all suppliers and ingredients they supply, and the ingredients that are not supplied by any supplier
SELECT S.SupplierName, I.IngredientName, I.Quantity/1000 as QuantityInKGs
FROM Supplier S
RIGHT JOIN canSupply cs ON S.SupplierID = cs.SupplierID
LEFT JOIN Ingredient I ON I.IngredientID = S.IngredientID;

--e. 2 queries with the IN operator and a subquery in the WHERE clause;
--in at least one case, the subquery must include a subquery in its own WHERE clause;

--chef's that work at Restaurants with more or 1 michelin star
SELECT C.FirstName, C.LastName
FROM Cook C
Inner join CookWorksOn CW ON C.CookID=CW.CookID
Inner Join RestaurantChain R ON R.RestaurantID=CW.RestaurantID
WHERE R.RestaurantID  IN (
    SELECT DISTINCT R2.RestaurantID
    FROM RestaurantChain R2
    WHERE R2.MichelinStars >= 1
);

--  restaurants where at least one supplier supplies organic ingredients
SELECT RestaurantName
FROM RestaurantChain
WHERE RestaurantID IN (
    SELECT DISTINCT RestaurantID
    FROM canSupply
    WHERE SupplierID IN (
        SELECT SupplierID
        FROM Supplier
        WHERE SupplierID IN (
            SELECT SupplierID
            FROM GetsFromAProducer
            WHERE ProducerID IN (
                SELECT ProducerID
                FROM Producer
                WHERE EcoProducts > 1
            )
			)
			)
	)

--f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

-- select recipe names for all the recipes with calories<300
Select R.RecipeName
From Recipe R
Where exists(
	Select *
	From Recipe R2
	Where R2.RecipeID=R.RecipeID
	And R2.Calories<300)

-- names of restaurants that have at least one waiter working the night shift
SELECT RestaurantName
FROM RestaurantChain R
WHERE EXISTS (
    SELECT *
    FROM WaiterWorksOn WW
    WHERE WW.RestaurantID = R.RestaurantID
    AND EXISTS (
        SELECT *
        FROM Waiter W
        WHERE W.WaiterID = WW.WaiterID
        AND W.WShift = 'Night'
    )
	)

--h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;


-- grouping the recipes by the calories and the minimum number of fats and showing the name for every such recipe
Select RecipeName,R1.Calories,R1.Fats,(R1.Calories+R1.Fats) as TotalMacros
From Recipe R1 Inner Join
	(Select R.Calories, Min(R.Fats) AS MinFats
	From Recipe R
	Group By R.Calories)R
ON R1.Calories=R.Calories And R.MinFats=R1.Fats
Order By TotalMacros


Select *
from Recipe

--gorup by the maximum experience of helper chefs that have experience bigger than 1

Select HC.Experience
From HelperChef HC
Group by HC.Experience
Having 1 < (Select Max(HC2.Experience)
From HelperChef HC2
Where HC2.Experience=HC.Experience)


--Select All the recipe names and calories for recipes with calories < 500 and a number of such recipes > 1 
--and the recipes to have the exact same number of calories 
Select RecipeName,R1.Calories,(R1.Calories/R1.Price) as CaloriesPerPrice
From Recipe R1 Inner Join(
Select R.Calories
From Recipe R
Where R.Calories<500
Group by R.Calories
Having count(*)>1)R ON R.Calories=R1.Calories



-- find the helper chefs that have experience bigger or equal than the average exprerience;
SELECT HC.HelperChefID,  AVG(HC.Experience) AS AverageExperience
FROM HelperChef HC
GROUP BY HC.HelperChefID, HC.Experience
HAVING HC.Experience >= (
    SELECT AVG(HC2.Experience)
    FROM HelperChef HC2
);
Select *
from Recipe


-- find the most expensive recipes among those with low fats content

select R.RecipeName, R.Price
From Recipe R
where R.Price > all(
	select R2.Price
	from Recipe R2
	where R2.Fats < 20)
Order by Price

-- using aggregation operator

select R.RecipeName, R.Price
From Recipe R
where R.Price > (
	select Max(R2.Price)
	from Recipe R2
	where R2.Fats < 20)



-- find all waiters that work on a restaurant at night shift (using in)
select W.FirstName,W.LastName,W.WShift
From Waiter W
where W.WaiterID in (
	Select W2.WaiterID
	From RestaurantChain R
	JOIN WaiterWorksOn WW ON R.RestaurantID = WW.RestaurantID
	JOIN Waiter W2 ON W2.WaiterID = WW.WaiterID
	where W2.Wshift='Night')

-- same as above but using any
select W.FirstName,W.LastName,W.WShift
From Waiter W
where W.WaiterID = any (
	Select W2.WaiterID
	From RestaurantChain R
	JOIN WaiterWorksOn WW ON R.RestaurantID = WW.RestaurantID
	JOIN Waiter W2 ON W2.WaiterID = WW.WaiterID
	where W2.Wshift='Night')
-- all the suppliers that are not expensive or are expensive but not working for a restaurant already.
select S.SupplierName
From Supplier S
where S.SupplierID <> ALL (
	Select Distinct S2.SupplierID
	From RestaurantChain R
	JOIN canSupply cs on R.RestaurantID =cs.RestaurantID
	Join Supplier S2 on cs.SupplierID=S2.SupplierID
	where S2.Price = 'Expensive')
	
-- same as above using not in

select S.SupplierName
From Supplier S
where S.SupplierID not in (
	Select Distinct S2.SupplierID
	From RestaurantChain R
	JOIN canSupply cs on R.RestaurantID =cs.RestaurantID
	Join Supplier S2 on cs.SupplierID=S2.SupplierID
	where S2.Price = 'Expensive')


-- select all the restaurant names that have more michelin stars then any restaurant that has at least 1 cook
Select R.RestaurantName
From RestaurantChain R
where R.MichelinStars > any (
		Select R2.MichelinStars
		From RestaurantChain R2
		JOIN CookWorksOn CO on R2.RestaurantID=CO.RestaurantID
		JOIN Cook C on C.CookID=CO.CookID)

--using aggregation operator
Select R.RestaurantName
From RestaurantChain R
where R.MichelinStars > (
		Select MIN(R2.MichelinStars) as MichelinStars
		From RestaurantChain R2
		JOIN CookWorksOn CO on R2.RestaurantID=CO.RestaurantID
		JOIN Cook C on C.CookID=CO.CookID)