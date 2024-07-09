USE Test




CREATE OR ALTER PROCEDURE sp_AddCookAndRestaurantWithPartialCommit
    @CookFirstName VARCHAR(50),
    @CookLastName VARCHAR(50),
    @CookSpecialization VARCHAR(50),
    @RestaurantName VARCHAR(50),
    @RestaurantAddress VARCHAR(50),
    @RestaurantPhone VARCHAR(50),
    @RestaurantMichelinStars INT
AS
BEGIN
    DECLARE @CookID INT;
    DECLARE @RestaurantID INT;
    
    -- Insert Cook
    BEGIN TRY
        BEGIN TRANSACTION;
        
        -- Validate Cook Details
         IF dbo.uf_ValidateStartsWithUppercase(@CookFirstName) = 0 OR
           dbo.uf_ValidateStartsWithUppercase(@CookLastName) = 0 OR
           dbo.uf_ValidateStartsWithUppercase(@CookSpecialization) = 0
        BEGIN
            RAISERROR('Cook details must start with an uppercase letter and not be null.', 16, 1);
        END

        INSERT INTO Cook (FirstName, LastName, Specialization) 
        VALUES (@CookFirstName, @CookLastName, @CookSpecialization);
        SET @CookID = SCOPE_IDENTITY();

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;
        -- Log error
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate,ErrorMessage) 
        VALUES ('Error Insert', 'Cook', GETDATE(), ERROR_MESSAGE());
		
    END CATCH

    -- Insert Restaurant
    BEGIN TRY
        BEGIN TRANSACTION;
        
        -- Validate Restaurant Details
        IF dbo.uf_ValidateStartsWithUppercase(@RestaurantName) = 0 OR
           dbo.uf_ValidatePhoneNumber(@RestaurantPhone) = 0 OR
           dbo.uf_ValidatePositiveInt(@RestaurantMichelinStars) = 0
        BEGIN
            RAISERROR('Restaurant details are not valid.', 16, 1);
        END
        INSERT INTO RestaurantChain (RestaurantName, Adress, Phone, MichelinStars) 
        VALUES (@RestaurantName, @RestaurantAddress, @RestaurantPhone, @RestaurantMichelinStars);
        SET @RestaurantID = SCOPE_IDENTITY();

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;
        -- Log error
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate,ErrorMessage) 
        VALUES ('Error Insert', 'RestaurantChain', GETDATE(), ERROR_MESSAGE());
		THROW
    END CATCH

    -- Insert CookWorksOn
    IF @CookID IS NOT NULL AND @RestaurantID IS NOT NULL
    BEGIN
        BEGIN TRY
            BEGIN TRANSACTION;

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
            INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate,ErrorMessage) 
            VALUES ('Error Insert', 'CookWorksOn', GETDATE(), ERROR_MESSAGE());
			THROW
        END CATCH
    END
END;

SELECT * FROM LogTable

EXEC sp_AddCookAndRestaurantWithPartialCommit 'john', 'Doe', 'Pastry', 'Gourmet Delight', '123 Food St', '555-1234', 3;
SELECT * FROM Cook;
SELECT * FROM RestaurantChain;
SELECT * FROM CookWorksOn;


EXEC sp_AddCookAndRestaurantWithPartialCommit 'John1', 'Doe', 'Pastry', 'gourmet elight', '123 Food St', '555-1234', -1;
SELECT * FROM Cook;
SELECT * FROM RestaurantChain;
SELECT * FROM CookWorksOn;
