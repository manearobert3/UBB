Use Test
GO
	--EXEC InsertRandomDataWRT @TestID=1;

	CREATE OR ALTER PROCEDURE InsertRandomDataWRT
		@TestID INT
	AS
	BEGIN
		DECLARE @Sql NVARCHAR(MAX) = '';
		DECLARE @ColumnType NVARCHAR(50);
		DECLARE @ColumnName NVARCHAR(255);
		DECLARE @ColumnMaxLength INT;
		DECLARE @Counter INT = 1;
		DECLARE @PrimaryKeyCount INT = 0;
		DECLARE @ForeignKeyCount INT = 0;
		DECLARE @ReferencedTableName NVARCHAR(255);
		DECLARE @RandomValue INT = 1;
		DECLARE @TotalColumnList NVARCHAR(MAX) = '';
		DECLARE @TotalValuesList NVARCHAR(MAX) = ''; 
		DECLARE @TableName NVARCHAR(50);
		DEclare @NumberOfRows INT;
		DECLARE @TableID INT;
		DECLARE @TestRunID INT;	
		DECLARE @StartTimeGlobal DATETIME, @EndTimeGlobal DATETIME;
		DECLARE @Description NVARCHAR(50);
		Set @StartTimeGlobal =GetDate();
		Select @TestRunID = COUNT(*) + 1
		FROM TestRuns;
		print @TestRunID;
	
		INSERT INTO TestRuns (Description, StartAt, EndAt)
		VALUES ('Initial Description', GETDATE(), GETDATE());

	
		-- Create a temporary table to store TableID values
		CREATE TABLE #TempTableIDs (TableID INT,NoRows INT,Position INT);

		-- Populate the temporary table with TableID values based on the provided TestID
		INSERT INTO #TempTableIDs (TableID,NoRows,Position)
		SELECT TableID,NoOfRows, Position
		FROM TestTables
		WHERE TestID = @TestID;
		Select * from #TempTableIDs
		Order by Position;
		
		DECLARE DeleteCursor CURSOR FOR
		SELECT t.TableID, t.NoRows, tt.Name
		FROM #TempTableIDs t
		JOIN Tables tt ON t.TableID = tt.TableID
		ORDER BY t.Position; -- Order by Position in order

		OPEN DeleteCursor;

		FETCH NEXT FROM DeleteCursor INTO @TableID, @NumberOfRows, @TableName;

		WHILE @@FETCH_STATUS = 0
		BEGIN
			-- Build the dynamic SQL DELETE statement
			SET @Sql = 'DELETE FROM ' + QUOTENAME(@TableName) + ';';
			print @Sql
			-- Execute the dynamic SQL
			EXEC sp_executesql @Sql;

			-- Fetch the next table for deletion
			FETCH NEXT FROM DeleteCursor INTO @TableID, @NumberOfRows, @TableName;
		END;

		CLOSE DeleteCursor;
		DEALLOCATE DeleteCursor;
		-- Loop through the tables associated with the provided TestID
		DECLARE TableCursor CURSOR FOR
		SELECT t.TableID, t.NoRows, tt.Name
		FROM #TempTableIDs t
		JOIN Tables tt ON t.TableID = tt.TableID
		Order by t.Position DESC;

		OPEN TableCursor;

		FETCH NEXT FROM TableCursor INTO @TableID, @NumberOfRows, @TableName;

		Print @TableName;
		Print @NumberOfRows
		WHILE @@FETCH_STATUS = 0
		BEGIN
			-- Reset the counter for each table
			SET @Counter = 1;

			-- Determine the number of primary key columns and foreign key columns for the current table
			SELECT @PrimaryKeyCount = COUNT(*)
			FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS TC
			WHERE TC.TABLE_NAME = @TableName AND TC.CONSTRAINT_TYPE = 'PRIMARY KEY';

			SELECT @ForeignKeyCount = COUNT(*)
			FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS TC
			WHERE TC.TABLE_NAME = @TableName AND TC.CONSTRAINT_TYPE = 'FOREIGN KEY';

			-- Loop for the specified number of rows
			WHILE @Counter <= @NumberOfRows
			BEGIN
			DECLARE @ColumnList NVARCHAR(MAX) = ''; -- Reset column list for each iteration
			DECLARE @ValuesList NVARCHAR(MAX) = ''; -- Reset values list for each iteration

			-- Get column information for the specified table
			DECLARE ColumnCursor CURSOR FOR
			SELECT COLUMN_NAME, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH
			FROM INFORMATION_SCHEMA.COLUMNS
			WHERE TABLE_NAME = @TableName;

			OPEN ColumnCursor;

			-- Fetch the first column
			FETCH NEXT FROM ColumnCursor INTO @ColumnName, @ColumnType, @ColumnMaxLength;

			-- Loop through columns
			WHILE @@FETCH_STATUS = 0
			BEGIN
				SET @ColumnList += QUOTENAME(@ColumnName) + ',';
				
				IF EXISTS (
					SELECT 1
					--Select RC.CONSTRAINT_Name
					FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU
					JOIN INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS RC
						ON KCU.CONSTRAINT_NAME = RC.CONSTRAINT_NAME
					WHERE KCU.TABLE_NAME = @TableName
						AND KCU.COLUMN_NAME = @ColumnName
				)
				BEGIN
					DECLARE @ConstraintName NVARCHAR(255); 
					Select @ConstraintName=RC.CONSTRAINT_Name
					FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU
					JOIN INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS RC
						ON KCU.CONSTRAINT_NAME = RC.CONSTRAINT_NAME
					WHERE KCU.TABLE_NAME = @TableName
						AND KCU.COLUMN_NAME = @ColumnName
					--SELECT @ConstraintName = RC.CONSTRAINT_NAME
					--FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS RC
					--WHERE RC.CONSTRAINT_NAME IN (
						--SELECT CONSTRAINT_NAME
						--FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU
						--WHERE TABLE_NAME = @TableName AND CONSTRAINT_NAME = RC.CONSTRAINT_NAME
						--WHERE TABLE_NAME = 'WaiterWorksOn' AND KCU.CONSTRAINT_NAME = RC.CONSTRAINT_NAME
					--);

					SELECT
						@ReferencedTableName = KCU2.TABLE_NAME
					FROM
						INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU1
					INNER JOIN
						INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS RC
						ON KCU1.CONSTRAINT_NAME = RC.CONSTRAINT_NAME
					INNER JOIN 
						INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU2
						ON RC.UNIQUE_CONSTRAINT_NAME = KCU2.CONSTRAINT_NAME
					WHERE
						KCU1.CONSTRAINT_NAME = @ConstraintName;

					SET @Sql = 'SELECT TOP 1 @RandomValue = ' + QUOTENAME(@ColumnName) +
							   ' FROM ' + QUOTENAME(@ReferencedTableName) +
							   ' ORDER BY NEWID();';

					-- Execute dynamic SQL to get the random value
					EXEC sp_executesql @Sql, N'@RandomValue INT OUTPUT', @RandomValue OUTPUT;

					-- Append the random value to @ValuesList
					SET @ValuesList += CAST(@RandomValue AS NVARCHAR(50)) + ',';
				END
				ELSE IF EXISTS (
					SELECT 1
					FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU
					JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS TC
						ON KCU.CONSTRAINT_NAME = TC.CONSTRAINT_NAME
					WHERE KCU.TABLE_NAME = @TableName
						AND KCU.COLUMN_NAME = @ColumnName
						AND TC.CONSTRAINT_TYPE = 'PRIMARY KEY'
				)
				BEGIN
					-- Generate random data based on data type
					IF @ColumnType IN ('int', 'smallint', 'tinyint', 'bigint','INT')
					SET @ValuesList += CAST(@Counter AS NVARCHAR(50)) + ',';
					ELSE IF @ColumnType IN ('nvarchar', 'varchar')
					SET @ValuesList += '''' + LEFT(CONVERT(NVARCHAR(255), NEWID()), 10) + ''',';
				END
				ELSE IF @ColumnType IN ('int', 'smallint', 'tinyint', 'bigint','INT')
					SET @ValuesList += CAST(ABS(CHECKSUM(NEWID())) % 1000 + 1 AS NVARCHAR(50)) + ',';
				ELSE IF @ColumnType IN ('float', 'real')
					SET @ValuesList += CAST(RAND() * 1000 AS NVARCHAR(50)) + ',';
				ELSE IF @ColumnType IN ('nvarchar', 'varchar')
					SET @ValuesList += '''' + LEFT(CONVERT(NVARCHAR(255), NEWID()), 10) + ''',';

				FETCH NEXT FROM ColumnCursor INTO @ColumnName, @ColumnType, @ColumnMaxLength;
			END

			CLOSE ColumnCursor;
			DEALLOCATE ColumnCursor;

			-- Remove trailing commas
			SET @ColumnList = LEFT(@ColumnList, LEN(@ColumnList) - 1);
			SET @ValuesList = LEFT(@ValuesList, LEN(@ValuesList) - 1);
		
			-- Accumulate column and values lists
			SET @TotalColumnList += @ColumnList + ',';
			SET @TotalValuesList += @ValuesList + '),(';

				-- Increment the counter
				SET @Counter = @Counter + 1;
			END;

			-- Remove trailing commas
			SET @TotalColumnList = LEFT(@TotalColumnList, LEN(@TotalColumnList) - 1);
			SET @TotalValuesList = LEFT(@TotalValuesList, LEN(@TotalValuesList) - 2); -- Remove the extra comma and open parenthesis
			DECLARE @StartTime DATETIME, @EndTime DATETIME;

			-- Build the dynamic SQL INSERT statement
			SET @Sql = 'INSERT INTO ' + QUOTENAME(@TableName) + ' (' + @ColumnList + ') VALUES (' + @TotalValuesList + ';';
			print @Sql
			SET @StartTime = GETDATE();
		
			-- Execute the dynamic SQL
			EXEC sp_executesql @Sql;
			SET @EndTime = GETDATE();


			--Set @Sql = 'INSERT INTO TestRunTables(TestRunID,TableID,StartAt,EndAt) Values('+@TestRunID+','+@TableID+','+@StartTime+','+@EndTime+')';
			INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@TestRunID, @TableID, @StartTime, @EndTime);
			--SET @Sql = 'INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@TestRunID, @TableID, @StartTime, @EndTime);';

	-- Execute the dynamic SQL with parameters
			--EXEC sp_executesql @Sql, 
			   --        N'@TestRunID INT, @TableID INT, @StartTime DATETIME, @EndTime DATETIME', 
			   --        @TestRunID, @TableID, @StartTime, @EndTime;
		
			--EXEC sp_executesql @Sql;
			SET @TotalValuesList = '';
			-- Fetch the next table
			FETCH NEXT FROM TableCursor INTO @TableID, @NumberOfRows, @TableName;
		END;

		CLOSE TableCursor;
		DEALLOCATE TableCursor;
		Set @EndTimeGlobal =GetDate();
	
		--Set @Sql = 'INSERT INTO TestRuns(TestRunID,Description,StartAt,EndAt) Values('+@TestRunID+','+'''Insert on ' + CAST(@TableID AS NVARCHAR(255)) + ''','+','+@StartTimeGlobal+','+@EndTimeGlobal+')';
		--Print @Sql
		--EXEC sp_executesql @Sql;
		--INSERT INTO TestRunTables(TestRunID,TableID,StartAt,EndAt) Values(@TestRunID,@TableID,@StartTimeGlobal,@EndTimeGlobal);
		SET @Description = 'Runned Test with ID:' + CONVERT(NVARCHAR(50), @TestRunID);
		UPDATE TestRuns
		SET
			Description = @Description,
			EndAt = GETDATE()    
		WHERE TestRunID = @TestRunID;
	
		Declare @ViewID INt;
		Declare @ViewName NVARCHAR(50);

		DECLARE ViewCursor CURSOR FOR
		SELECT ViewID
		FROM TestViews
		WHERE TestID = @TestID;
	
		OPEN ViewCursor;
		
		print @TestID;

		-- 2. Loop through each ViewID
		FETCH NEXT FROM ViewCursor INTO @ViewID;
		IF @@FETCH_STATUS <> 0
BEGIN
    PRINT 'No rows fetched from ViewCursor.';
END
ELSE
BEGIN
    PRINT 'Rows fetched from ViewCursor.';
	END
	

		WHILE @@FETCH_STATUS = 0
		BEGIN
			-- 3. Retrieve the corresponding Name from the Views table
			SELECT @ViewName = Name
			FROM Views
			WHERE ViewID = @ViewID;
			print @ViewName;
			-- Construct dynamic SQL statement to execute the specific view
			SET @StartTime = GETDATE();
			SET @Sql = 'SELECT * FROM ' + QUOTENAME(@ViewName);
			print @Sql;
			-- Execute the dynamic SQL
			EXEC sp_executesql @Sql;
			SET @EndTime = GETDATE();
		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@TestRunID, @ViewID, @StartTime, @EndTime);
		
			-- Fetch the next ViewID
			FETCH NEXT FROM ViewCursor INTO @ViewID;
		END;
			CLOSE ViewCursor;
		DEALLOCATE ViewCursor;
		-- Drop the temporary table
		DROP TABLE #TempTableIDs;
	END