ALTER DATABASE Test SET ALLOW_SNAPSHOT_ISOLATION ON;
Select * from LogTable
USE Test;
BEGIN TRY
	BEGIN TRANSACTION;
	SET TRANSACTION ISOLATION LEVEL SNAPSHOT;
	SELECT * FROM Cook WHERE CookID = 1;
	-- Should show initial value
	WAITFOR DELAY '00:00:05';
	UPDATE Cook SET Specialization = 'Mexican' WHERE CookID = 1;
	-- This update may fail if the data has been modified by Transaction 1
	COMMIT TRANSACTION;
	INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 2 Update Conflict', GETDATE(), 'Transaction successful');
END TRY
BEGIN CATCH
    -- Handle the error and rollback if necessary
    IF XACT_STATE() <> 0
    BEGIN
        ROLLBACK TRANSACTION;
    END
    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 2 Update Conflict', GETDATE(), ERROR_MESSAGE());
END CATCH;


-- without log
ALTER DATABASE Test SET ALLOW_SNAPSHOT_ISOLATION ON;
BEGIN TRANSACTION;
	SET TRANSACTION ISOLATION LEVEL SNAPSHOT;
	SELECT * FROM Cook WHERE CookID = 1;
	-- Should show initial value
	WAITFOR DELAY '00:00:05';
	UPDATE Cook SET Specialization = 'Mexican' WHERE CookID = 1;
	-- This update may fail if the data has been modified by Transaction 1
	COMMIT TRANSACTION;