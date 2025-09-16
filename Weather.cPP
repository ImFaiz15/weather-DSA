//The weather data storage system 
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits> 

struct WeatherRecord {
    std::string date;       
    std::string city;
    double temperature;
};

//Step 2 & 3 & 4: Implement the Data Storage System 
class WeatherDataSystem {
private:
    std::vector<std::vector<double>> temperatureData;

    std::map<int, int> year_to_row_index;
    std::map<std::string, int> city_to_col_index;

    std::vector<int> years;
    std::vector<std::string> cities;

    const double SENTINEL_VALUE = -999.0;

public:
    WeatherDataSystem(const std::vector<int>& p_years, const std::vector<std::string>& p_cities) {
        years = p_years;
        cities = p_cities;

        for (int i = 0; i < years.size(); ++i) {
            year_to_row_index[years[i]] = i;
        }
        for (int i = 0; i < cities.size(); ++i) {
            city_to_col_index[cities[i]] = i;
        }

        temperatureData.resize(years.size(), std::vector<double>(cities.size(), SENTINEL_VALUE));
    }

    void insert(int year, const std::string& city, double temp) {
        if (year_to_row_index.count(year) && city_to_col_index.count(city)) {
            int rowIndex = year_to_row_index[year];
            int colIndex = city_to_col_index[city];
            temperatureData[rowIndex][colIndex] = temp;
            std::cout << "Inserted: Year " << year << ", City " << city << ", Temp " << temp << " C" << std::endl;
        } else {
            std::cout << "Error: Year or City not found in the system." << std::endl;
        }
    }

    void remove(int year, const std::string& city) {
        if (year_to_row_index.count(year) && city_to_col_index.count(city)) {
            int rowIndex = year_to_row_index[year];
            int colIndex = city_to_col_index[city];
            temperatureData[rowIndex][colIndex] = SENTINEL_VALUE;
            std::cout << "Deleted data for Year " << year << ", City " << city << std::endl;
        } else {
            std::cout << "Error: Cannot delete, Year or City not found." << std::endl;
        }
    }

    void retrieve(int year, const std::string& city) {
        if (year_to_row_index.count(year) && city_to_col_index.count(city)) {
            int rowIndex = year_to_row_index[year];
            int colIndex = city_to_col_index[city];
            double temp = temperatureData[rowIndex][colIndex];
            
            if (temp == SENTINEL_VALUE) {
                std::cout << "Data for Year " << year << ", City " << city << " is not available (sparse data)." << std::endl;
            } else {
                std::cout << "Retrieved: Temp for Year " << year << ", City " << city << " is " << temp << " C" << std::endl;
            }
        } else {
            std::cout << "Error: Cannot retrieve, Year or City not found." << std::endl;
        }
    }


    void displayRowMajor() {
        std::cout << "\n--- Displaying Data (Row-Major Access) ---\n";
        for (int i = 0; i < years.size(); ++i) {
            std::cout << "Year " << years[i] << ": ";
            for (int j = 0; j < cities.size(); ++j) {
                if(temperatureData[i][j] == SENTINEL_VALUE) std::cout << "N/A\t";
                else std::cout << temperatureData[i][j] << "C\t";
            }
            std::cout << std::endl;
        }
    }

    void displayColumnMajor() {
        std::cout << "\n--- Displaying Data (Column-Major Access) ---\n";
        for (int j = 0; j < cities.size(); ++j) {
            std::cout << "City " << cities[j] << ": ";
            for (int i = 0; i < years.size(); ++i) {
                if(temperatureData[i][j] == SENTINEL_VALUE) std::cout << "N/A\t";
                 else std::cout << temperatureData[i][j] << "C (" << years[i] << ")\t";
            }
            std::cout << std::endl;
        }
    }
};

//Main function 
int main() {
    std::vector<int> years = {2023, 2024, 2025};
    std::vector<std::string> cities = {"Delhi", "Mumbai", "Kolkata", "Chennai"};

    WeatherDataSystem weatherDB(years, cities);

    std::cout << "--- Populating Data ---\n";
    weatherDB.insert(2023, "Delhi", 25.5);
    weatherDB.insert(2024, "Delhi", 26.1);
    weatherDB.insert(2024, "Mumbai", 28.2);
    weatherDB.insert(2025, "Chennai", 30.5);
    weatherDB.insert(2023, "Kolkata", 27.8);
    weatherDB.insert(2023, "Bengaluru", 22.9);

    // Display 
    weatherDB.displayRowMajor();

    std::cout << "\n--- Retrieving and Deleting Data ---\n";
    weatherDB.retrieve(2024, "Haryana"); 
    weatherDB.retrieve(2025, "Delhi");  
    weatherDB.remove(2024, "Mumbai");   
    weatherDB.retrieve(2024, "Mumbai"); 

    // Display again 
    weatherDB.displayRowMajor();
    
    return 0;
}
