#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

//Constants and global variables
#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0

// Global arrays for system data
char cities[MAX_CITIES][MAX_NAME_LENGTH];  //Array to store city names
float distance[MAX_CITIES][MAX_CITIES];  //2D array for distance matrix
int city_count = 0;  //Counter for number of cities

// Global variables for delivery records
int delivery_ids[MAX_DELIVERIES];
char delivery_sources[MAX_DELIVERIES][MAX_NAME_LENGTH];
char delivery_destinations[MAX_DELIVERIES][MAX_NAME_LENGTH];
float delivery_weights[MAX_DELIVERIES];
char delivery_vehicles[MAX_DELIVERIES][10];
float delivery_distances[MAX_DELIVERIES];
int delivery_count = 0;
float delivery_base_costs[MAX_DELIVERIES];
float delivery_fuel_used[MAX_DELIVERIES];
float delivery_fuel_costs[MAX_DELIVERIES];
float delivery_operational_costs[MAX_DELIVERIES];
float delivery_profits[MAX_DELIVERIES];
float delivery_customer_charges[MAX_DELIVERIES];
float delivery_estimated_times[MAX_DELIVERIES];

// Vehicle data stored in parallel arrays
char vehicle_types[3][10] = {"Van", "Truck", "Lorry"};
int vehicle_capacities[3] = {1000, 5000, 10000};
float vehicle_rates[3] = {30.0, 40.0, 80.0};
float vehicle_speeds[3] = {60.0, 50.0, 45.0};
float vehicle_efficiencies[3] = {12.0, 6.0, 4.0};

// Function prototypes
void initialize_system();
void display_main_menu();
int get_valid_int_input(char* prompt, int min, int max);
float get_valid_float_input(char* prompt, float min, float max);
void clear_input_buffer();
int find_city_index(char* city_name);
void city_management();
void add_city();
void display_cities();
void rename_city();
void remove_city();
void distance_management();
void input_distance();
void display_distance_table();
float dijkstra_shortest_path(int source, int destination, int* path, int* path_length);
void process_delivery();
void generate_reports();
void display_summary_report();

int main()
{
    initialize_system();
    int choice;
    do {
        display_main_menu();
        choice = get_valid_int_input("Enter your choice: ", 0, 5);

        switch(choice) {
            case 1:
                city_management();  // Manage cities (add, rename, remove, display)
                break;
            case 2:
                distance_management();  // Manage distances between cities
                break;
            case 3:
                process_delivery();  // Process a new delivery request
                break;
            case 4:
                generate_reports();
                break;
            case 5:
                //To be implemented
                break;
            case 0:
                //To be implemented
                printf("Thank you for using Logistics Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);

    return 0;
}

void initialize_system() {
    // Initialize distance matrix
    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            if(i == j)
                distance[i][j] = 0;  // Distance from a city to itself is 0
            else
                distance[i][j] = -1; //No connection
        }
    }

    // Initialize delivery IDs to -1 (indicating empty slot)
    for(int i = 0; i < MAX_DELIVERIES; i++) {
        delivery_ids[i] = -1;
    }
}

// Display the main menu of the logistics management system
void display_main_menu() {
    printf("\n========================================\n");
    printf("   LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. City Management\n");
    printf("2. Distance Management\n");
    printf("3. Process Delivery\n");
    printf("4. Reports\n");
    printf("5. Save Data\n");
    printf("0. Exit\n");
    printf("========================================\n");
}

// Get valid integer input from user with range checking
int get_valid_int_input(char* prompt, int min, int max) {
    int value;
    while(1) {
        printf("%s", prompt);
        if(scanf("%d", &value) == 1) {
            if(value >= min && value <= max) {
                clear_input_buffer();
                return value;
            }
        }
        printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
        clear_input_buffer();
    }
}

// Clear the input buffer to prevent input issues
void clear_input_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Find the index of a city in the cities array by name
int find_city_index(char* city_name) {
    for(int i = 0; i < city_count; i++) {
        if(strcmp(cities[i], city_name) == 0) {
            return i;  // Return index if city found
        }
    }
    return -1;  // Return -1 if city not found
}

// Manage cities: add, rename, remove, or display cities
void city_management() {
    int choice;
    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Display Cities\n");
        printf("0. Back to Main Menu\n");

        choice = get_valid_int_input("Enter your choice: ", 0, 4);

        switch(choice) {
            case 1:
                add_city();
                break;
            case 2:
                rename_city();
                break;
            case 3:
                remove_city();
                break;
            case 4:
                display_cities();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);
}

// Add a new city to the system
void add_city() {
    if(city_count >= MAX_CITIES) {
        printf("Maximum number of cities (%d) reached!\n", MAX_CITIES);
        return;
    }

    char city_name[MAX_NAME_LENGTH];
    printf("Enter city name: ");
    scanf("%49s", city_name);
    clear_input_buffer();

    if(find_city_index(city_name) != -1) {
        printf("City '%s' already exists!\n", city_name);
        return;
    }

    strcpy(cities[city_count], city_name);
    city_count++;
    printf("City '%s' added successfully!\n", city_name);
}

// Display all available cities in the system
void display_cities() {
    printf("\n--- Available Cities ---\n");
    if(city_count == 0) {
        printf("No cities available.\n");
        return;
    }

    for(int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
}

// Rename an existing city
void rename_city() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    display_cities();
    int index = get_valid_int_input("Enter city number to rename: ", 1, city_count) - 1;

    char new_name[MAX_NAME_LENGTH];
    printf("Enter new name for %s: ", cities[index]);
    scanf("%49s", new_name);
    clear_input_buffer();

    if(find_city_index(new_name) != -1) {
        printf("City '%s' already exists!\n", new_name);
        return;
    }

    printf("City '%s' renamed to '%s'\n", cities[index], new_name);
    strcpy(cities[index], new_name);
}

// Remove a city from the system
void remove_city() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    display_cities();
    int index = get_valid_int_input("Enter city number to remove: ", 1, city_count) - 1;

    // Confirm removal with user
    printf("Are you sure you want to remove '%s'? (1=Yes, 0=No): ", cities[index]);
    int confirm = get_valid_int_input("", 0, 1);

    if(confirm) {
        // Shift array to remove city
        char removed_city[MAX_NAME_LENGTH];
        strcpy(removed_city, cities[index]);

        for(int i = index; i < city_count - 1; i++) {
            strcpy(cities[i], cities[i + 1]);
        }
        city_count--;

        printf("City '%s' removed successfully!\n", removed_city);
    }
}

// Manage distances between cities
void distance_management() {
    int choice;
    do {
        printf("\n--- Distance Management ---\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("0. Back to Main Menu\n");

        choice = get_valid_int_input("Enter your choice: ", 0, 2);

        switch(choice) {
            case 1:
                input_distance();  // Input or edit distance between two cities
                break;
            case 2:
                display_distance_table();  // Display the complete distance table
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);
}

// Get valid float input from user with range checking
float get_valid_float_input(char* prompt, float min, float max) {
    float value;
    while(1) {
        printf("%s", prompt);
        if(scanf("%f", &value) == 1) {
            if(value >= min && value <= max) {
                clear_input_buffer();
                return value;
            }
        }
        printf("Invalid input! Please enter a number between %.2f and %.2f.\n", min, max);
        clear_input_buffer();
    }
}

// Input or edit distance between two cities
void input_distance() {
    if(city_count < 2) {
        printf("Need at least 2 cities to input distances!\n");
        return;
    }

    display_cities();
    int city1 = get_valid_int_input("Enter first city number: ", 1, city_count) - 1;
    int city2 = get_valid_int_input("Enter second city number: ", 1, city_count) - 1;

    if(city1 == city2) {
        printf("Distance between same city is always 0.\n");
        return;
    }

    float dist = get_valid_float_input("Enter distance (km): ", 0.1, 10000.0);

    // Set symmetrical distance (both directions same)
    distance[city1][city2] = dist;
    distance[city2][city1] = dist;  // Symmetrical
    printf("Distance between %s and %s set to %.2f km\n", cities[city1], cities[city2], dist);
}

// Display the complete distance table between all cities
void display_distance_table() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n--- Distance Table (km) ---\n");

    // Header row
    printf("%-15s", "");
    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    // Data rows
    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for(int j = 0; j < city_count; j++) {
            if(distance[i][j] == -1)
                printf("%-15s", "N/A");  // Show N/A for unknown distances
            else
                printf("%-15.2f", distance[i][j]);  //Show distance value
        }
        printf("\n");
    }
}

// Dijkstra's algorithm to find shortest path between two cities
float dijkstra_shortest_path(int source, int destination, int* path, int* path_length) {
    float dist[MAX_CITIES];  // Array to store shortest distances from source
    int visited[MAX_CITIES] = {0};  // Array to track visited cities
    int previous[MAX_CITIES];  // Array to store previous city in shortest path

    for(int i = 0; i < MAX_CITIES; i++) {
        dist[i] = FLT_MAX;  // FLT_MAX represents infinity
        previous[i] = -1;  // -1 represents no previous city
    }
    dist[source] = 0;  // Distance from source to itself is 0

    // Process all cities
    for(int count = 0; count < city_count; count++) {
        // Find the unvisited city with minimum distance
        int min_index = -1;
        float min_dist = FLT_MAX;
        for(int v = 0; v < city_count; v++) {
            if(!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                min_index = v;
            }
        }

        if(min_index == -1) break;  // No more reachable cities
        visited[min_index] = 1;  // Mark city as visited

        // Update distances of adjacent cities
        for(int v = 0; v < city_count; v++) {
            if(!visited[v] && distance[min_index][v] > 0 &&           // If connected and unvisited
               dist[min_index] != FLT_MAX &&                          // If current city is reachable
               dist[min_index] + distance[min_index][v] < dist[v]) {  // If new path is shorter
                dist[v] = dist[min_index] + distance[min_index][v];   // Update distance
                previous[v] = min_index;                              // Update previous city
            }
        }
    }

    // Reconstruct the path from destination to source
    *path_length = 0;
    int current = destination;
    while(current != -1) {
        path[(*path_length)++] = current;  // Add city to path
        current = previous[current];  //Move to previous city
    }

    // Reverse the path to get source to destination order
    for(int i = 0; i < *path_length / 2; i++) {
        int temp = path[i];
        path[i] = path[*path_length - i - 1];
        path[*path_length - i - 1] = temp;
    }

    return dist[destination];  // Return the shortest distance
}

// Process a new delivery request
void process_delivery() {
    if(city_count < 2) {
        printf("Need at least 2 cities to process delivery!\n");
        return;
    }

    if(delivery_count >= MAX_DELIVERIES) {
        printf("Maximum delivery records (%d) reached!\n", MAX_DELIVERIES);
        return;
    }

    printf("\n--- Process Delivery ---\n");
    display_cities();

    // Get route information
    int source = get_valid_int_input("Enter source city number: ", 1, city_count) - 1;
    int destination = get_valid_int_input("Enter destination city number: ", 1, city_count) - 1;

    if(source == destination) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    // Find shortest path using Dijkstra's algorithm
    int path[MAX_CITIES];
    int path_length;
    float min_distance = dijkstra_shortest_path(source, destination, path, &path_length);

    if(min_distance == FLT_MAX) {
        printf("No route found between %s and %s!\n", cities[source], cities[destination]);
        return;
    }

    // Display route
    printf("\nShortest route: ");
    for(int i = 0; i < path_length; i++) {
        printf("%s", cities[path[i]]);
        if(i < path_length - 1) printf(" -> ");
    }
    printf(" (%.2f km)\n", min_distance);

    //Vehicle selection
    printf("\nAvailable Vehicles:\n");
    printf("1. Van (Capacity: %dkg, Rate: LKR%.2f/km)\n", vehicle_capacities[0], vehicle_rates[0]);
    printf("2. Truck (Capacity: %dkg, Rate: LKR%.2f/km)\n", vehicle_capacities[1], vehicle_rates[1]);
    printf("3. Lorry (Capacity: %dkg, Rate: LKR%.2f/km)\n", vehicle_capacities[2], vehicle_rates[2]);

    int vehicle_choice = get_valid_int_input("Select vehicle (1-3): ", 1, 3) - 1;
    float weight = get_valid_float_input("Enter package weight (kg): ", 0.1, vehicle_capacities[vehicle_choice]);

    // Calculations
    float base_cost = min_distance * vehicle_rates[vehicle_choice] * (1 + weight / 10000.0);
    float fuel_used = min_distance / vehicle_efficiencies[vehicle_choice];
    float fuel_cost = fuel_used * FUEL_PRICE;
    float operational_cost = base_cost + fuel_cost;
    float profit = base_cost * 0.25;
    float customer_charge = operational_cost + profit;
    float estimated_time = min_distance / vehicle_speeds[vehicle_choice];

    // Store delivery record
    int current_index = delivery_count;
    delivery_ids[current_index] = delivery_count + 1;
    strcpy(delivery_sources[current_index], cities[source]);
    strcpy(delivery_destinations[current_index], cities[destination]);
    delivery_weights[current_index] = weight;
    strcpy(delivery_vehicles[current_index], vehicle_types[vehicle_choice]);
    delivery_distances[current_index] = min_distance;
    delivery_base_costs[current_index] = base_cost;
    delivery_fuel_used[current_index] = fuel_used;
    delivery_fuel_costs[current_index] = fuel_cost;
    delivery_operational_costs[current_index] = operational_cost;
    delivery_profits[current_index] = profit;
    delivery_customer_charges[current_index] = customer_charge;
    delivery_estimated_times[current_index] = estimated_time;

    delivery_count++;

    // Display delivery summary
    printf("\n");
    printf("==============================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("==============================================================\n");
    printf("From: %s\n", cities[source]);
    printf("To: %s\n", cities[destination]);
    printf("Minimum Distance: %.0f km\n", min_distance);
    printf("Vehicle: %s\n", vehicle_types[vehicle_choice]);
    printf("Weight: %.0f kg\n", weight);
    printf("==============================================================\n");
    printf("Base Cost: %.0f x %.0f x (1 + %.0f/10000) = %s%.2f LKR\n",
           min_distance, vehicle_rates[vehicle_choice], weight,
           base_cost >= 10000 ? "" : "", base_cost);
    printf("Fuel Used: %.2f L\n", fuel_used);
    printf("Fuel Cost: %.2f LKR\n", fuel_cost);
    printf("Operational Cost: %.2f LKR\n", operational_cost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customer_charge);
    printf("Estimated Time: %.2f hours\n", estimated_time);
    printf("==============================================================\n");
}

void generate_reports() {
    if(delivery_count == 0) {
        printf("No delivery records available!\n");
        return;
    }

    int report_choice;
    do {
        printf("\n--- Performance Reports ---\n");
        printf("1. Summary Report\n");
        printf("2. Delivery History\n");
        printf("3. Vehicle Performance\n");
        printf("0. Back to Main Menu\n");

        report_choice = get_valid_int_input("Select report type: ", 0, 3);

        switch(report_choice) {
            case 1:
                display_summary_report();
                break;
            case 2:
                //To be implemented
                break;
            case 3:
                //To be implemented
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(report_choice != 0);
}

void display_summary_report() {
    printf("\n========================================\n");
    printf("        PERFORMANCE SUMMARY REPORT\n");
    printf("========================================\n");

    float total_distance = 0;
    float total_time = 0;
    float total_revenue = 0;
    float total_profit = 0;
    float longest_route = 0;
    float shortest_route = FLT_MAX;

    for(int i = 0; i < delivery_count; i++) {
        total_distance += delivery_distances[i];
        total_time += delivery_estimated_times[i];
        total_revenue += delivery_customer_charges[i];
        total_profit += delivery_profits[i];

        if(delivery_distances[i] > longest_route)
            longest_route = delivery_distances[i];
        if(delivery_distances[i] < shortest_route)
            shortest_route = delivery_distances[i];
    }

    float average_delivery_time = total_time / delivery_count;

    // Display all required metrics
    printf("a. Total Deliveries Completed: %d\n", delivery_count);
    printf("b. Total Distance Covered: %.2f km\n", total_distance);
    printf("c. Average Delivery Time: %.2f hours\n", average_delivery_time);
    printf("d. Total Revenue: LKR %.2f\n", total_revenue);
    printf("   Total Profit: LKR %.2f\n", total_profit);
    printf("e. Longest Route Completed: %.2f km\n", longest_route);
    printf("   Shortest Route Completed: %.2f km\n",
           (shortest_route == FLT_MAX) ? 0 : shortest_route);

    // Additional useful metrics
    printf("\nAdditional Metrics:\n");
    printf(" Average Distance per Delivery: %.2f km\n", total_distance / delivery_count);
    printf(" Average Revenue per Delivery: LKR %.2f\n", total_revenue / delivery_count);
    printf(" Total Fuel Cost: LKR %.2f\n", total_revenue - total_profit - (total_revenue * 0.8));

    printf("========================================\n");
}
