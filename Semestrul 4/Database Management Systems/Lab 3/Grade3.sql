USE Test
CREATE TABLE LogTable(
    Lid INT IDENTITY PRIMARY KEY,
    TypeOperation VARCHAR(50),
    TableOperation VARCHAR(50),
    ExecutionDate DATETIME,
    ErrorMessage VARCHAR(MAX)  -- Optional, to store error messages if needed
);

DROP TABLE IF EXISTS Cook;

-- Recreate the table
CREATE TABLE Cook (
    CookID INT IDENTITY(1,1) PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Specialization VARCHAR(50)
);

-- Validation functions for the procedures

-- Validate if the string starts with uppercase

CREATE OR ALTER FUNCTION uf_ValidateStartsWithUppercase (@input VARCHAR(100)) RETURNS INT AS
BEGIN
    DECLARE @return INT = 0;
    -- Check first if the input is not NULL
    IF (@input IS NOT NULL AND @input COLLATE Latin1_General_BIN LIKE '[A-Z]%')
        SET @return = 1;
    RETURN @return;
END;


-- Function to ensure an integer is positive

CREATE FUNCTION uf_ValidatePositiveInt (@number INT) RETURNS INT AS
BEGIN
    DECLARE @return INT = 0;
    IF (@number > 0)
        SET @return = 1;
    RETURN @return;
END;

-- Function to validate phone number ('999-9999' or '999 9999')

CREATE FUNCTION uf_ValidatePhoneNumber (@phone VARCHAR(50)) RETURNS INT AS
BEGIN
    DECLARE @return INT = 0;
    IF @phone LIKE '[0-9]%' AND @phone NOT LIKE '%[^0-9 -]%' -- Allow numbers, spaces, dashes
        SET @return = 1;
    RETURN @return;
END;

USE Test
CREATE OR ALTER PROCEDURE sp_AddCookAndRestaurantWithRollback
    @CookFirstName VARCHAR(50),
    @CookLastName VARCHAR(50),
    @CookSpecialization VARCHAR(50),
    @RestaurantName VARCHAR(50),
    @RestaurantAddress VARCHAR(50),
    @RestaurantPhone VARCHAR(50),
    @RestaurantMichelinStars INT
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

        -- Validate Cook Details
        IF dbo.uf_ValidateStartsWithUppercase(@CookFirstName) = 0 OR
           dbo.uf_ValidateStartsWithUppercase(@CookLastName) = 0 OR
           dbo.uf_ValidateStartsWithUppercase(@CookSpecialization) = 0
        BEGIN
            RAISERROR('Cook details must start with an uppercase letter and not be null.', 16, 1);
        END

        -- Validate Restaurant Details
        IF dbo.uf_ValidateStartsWithUppercase(@RestaurantName) = 0 OR
           dbo.uf_ValidatePhoneNumber(@RestaurantPhone) = 0 OR
           dbo.uf_ValidatePositiveInt(@RestaurantMichelinStars) = 0
        BEGIN
            RAISERROR('Restaurant details are not valid.', 16, 1);
        END

        -- Insert Cook
        INSERT INTO Cook (FirstName, LastName, Specialization) 
        VALUES (@CookFirstName, @CookLastName, @CookSpecialization);
        DECLARE @CookID INT = SCOPE_IDENTITY();

        -- Insert Restaurant
        INSERT INTO RestaurantChain (RestaurantName, Adress, Phone, MichelinStars) 
        VALUES (@RestaurantName, @RestaurantAddress, @RestaurantPhone, @RestaurantMichelinStars);
        DECLARE @RestaurantID INT = SCOPE_IDENTITY();

        -- Insert CookWorksOn
        INSERT INTO CookWorksOn (RestaurantID, CookID) 
        VALUES (@RestaurantID, @CookID);

        COMMIT TRANSACTION;

		-- Log successful transaction

			INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage) 
            VALUES ('Success', 'All Transactions', GETDATE(), 'Transaction successful');

    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;
        -- Log error
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage) 
        VALUES ('Error Insert', 'Cook, RestaurantChain, CookWorksOn', GETDATE(), ERROR_MESSAGE());

        THROW; -- Re-throwing caught exception
    END CATCH
END;
SELECT * FROM LogTable

EXEC sp_AddCookAndRestaurantWithRollback 'John', 'Doe', 'Pastry', 'Gourmet Delight', '123 Food St', '555-1234', 3;
SELECT * FROM Cook;
SELECT * FROM RestaurantChain;
SELECT * FROM CookWorksOn;



EXEC sp_AddCookAndRestaurantWithRollback NULL, 'Doe', 'Pastry', 'Gourmet Delight', '123 Food St', '555-1234', 3;
SELECT * FROM Cook;
SELECT * FROM RestaurantChain;
SELECT * FROM CookWorksOn;
