USE Test;
CREATE TABLE LogTable (
    Lid INT IDENTITY PRIMARY KEY,
    TypeOperation VARCHAR(50),
    TableOperation VARCHAR(50),
    ExecutionDate DATETIME,
    ErrorMessage VARCHAR(MAX)
);

CREATE TABLE LogChanges (
    Lid INT IDENTITY PRIMARY KEY,
    currentTime DATETIME,
    info VARCHAR(100),
    oldData VARCHAR(100),
    newData VARCHAR(100),
    error VARCHAR(1000)
);

CREATE OR ALTER PROCEDURE log_changes2
    @oldData VARCHAR(100),
    @newData VARCHAR(100),
    @info VARCHAR(100),
    @error VARCHAR(100)
AS
BEGIN
    BEGIN TRANSACTION;
    INSERT INTO LogChanges (currentTime, info,oldData, newData, error)
    VALUES (GETDATE(), @info,@oldData, @newData, @error)
	COMMIT TRANSACTION;

END;

EXEC log_changes2 'ASD', 'ASD', 'Transaction 1 Dirty Reads: Update RestaurantChain',NULL;
Select * from LogTable;
SELECT * FROM LogChanges;
BEGIN TRY
    BEGIN TRANSACTION;

    -- Log the old value before the update
    DECLARE @oldData INT;
    DECLARE @newData INT;
    SELECT @oldData = MichelinStars FROM RestaurantChain WHERE RestaurantID = 1;

    -- Perform the update
    UPDATE RestaurantChain SET MichelinStars = 5 WHERE RestaurantID = 1;

    -- Log the new value after the update
    SELECT @newData = MichelinStars FROM RestaurantChain WHERE RestaurantID = 1;
    EXEC log_changes2 @oldData, @newData, 'Transaction 1 Dirty Reads: Update RestaurantChain',NULL;

    WAITFOR DELAY '00:00:10';
    ROLLBACK TRANSACTION;

    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 1 Dirty Reads', GETDATE(), 'Transaction successful');
END TRY
BEGIN CATCH
    -- Handle the error and rollback if necessary
    IF XACT_STATE() <> 0
    BEGIN
        ROLLBACK TRANSACTION;
    END
    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 1 Dirty Reads', GETDATE(), ERROR_MESSAGE());
END CATCH;
