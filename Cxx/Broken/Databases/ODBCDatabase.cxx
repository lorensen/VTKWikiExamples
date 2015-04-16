  //This is the format for using the Microsoft Access ODBC Driver connection string.
  //DRIVER={Microsoft Access Driver (*.mdb)};Dbq=C:\mydatabase.mdb;Uid=Admin;Pwd=;
  //The keyword DRIVER must be in all caps for vtkODBCDatabase to work with any data source with the word "Driver" in it.
  //Many odbc examples online have it in lower case.
 
  //Create Database object
  vtkODBCDatabase* db = vtkODBCDatabase::New();

            
  //Set the data source name. Do not include the user id or password in this string. They are set with separate functions.
  db->SetDataSourceName("DRIVER={Microsoft Access Driver (*.mdb)};Dbq=C:\\mydatabase.mdb;"); 
  db->SetUserName("Admin");
  db->SetPassword("password"); 

  //Open the database
  bool status = db->Open(NULL);

  //Check if we successfully opened the database
  if(!status)
    {
    const char* err = db->GetLastErrorText();
    return;
    }

  //Retrieve the usable query object from the database instance
  vtkSQLQuery* query = db->GetQueryInstance(); 

  //Set the query text. This can be any valid SQL statement that the database supports
  query->SetQuery("Select CenterLon, CenterLat FROM Sites WHERE SiteID = 'KUEX'"); 

  //Execute the query. There are several options for retreiving data (fill tables, get rows, ...)
  if (query->Execute())
    {
    while(query->NextRow())
      {
      latlon[0] = query->DataValue(0).ToDouble();
      latlon[1] = query->DataValue(1).ToDouble();
      }
    }
  else
    {
      const char* err = query->GetLastErrorText();
    } 

  db->Close();
  query->Delete();
  db->Delete();
