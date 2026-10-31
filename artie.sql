-- ====================| SCHEMA DEFINITION |====================

-- cleanup
DROP TABLE IF EXISTS slot;
DROP TABLE IF EXISTS composition;
DROP TABLE IF EXISTS plan;
DROP TABLE IF EXISTS meal;
DROP TABLE IF EXISTS ingredient;

-- enable integrity checks on foreign keys
PRAGMA foreign_keys = ON;

-- e: ingredient
CREATE TABLE IF NOT EXISTS ingredient (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    category TEXT CHECK(category IN ('carb','prot','fat')),
    macro_prop REAL NOT NULL,
    cal REAL NOT NULL
);

-- e: meal
CREATE TABLE IF NOT EXISTS meal (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    category TEXT CHECK(category IN ('full','snack'))
);

-- e: plan
CREATE TABLE plan (
    id INTEGER PRIMARY KEY,
    day_of_week TEXT CHECK(day_of_week IN ('mon', 'tue', 'wed', 'thu', 'fri', 'sat', 'sun')) NOT NULL,
    date_calendar TEXT
);

-- r[ingredient<->meal]: composition
CREATE TABLE IF NOT EXISTS composition (
    id_meal INTEGER,
    id_ingredient INTEGER,
    portion REAL NOT NULL,
    PRIMARY KEY (id_meal, id_ingredient),
    CONSTRAINT fk_meal_composition
       FOREIGN KEY (id_meal) REFERENCES meal(id)
       ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_ingredient_composition
       FOREIGN KEY (id_ingredient) REFERENCES ingredient(id)
       ON DELETE CASCADE ON UPDATE CASCADE
);

-- r[meal<->plan]: slot
CREATE TABLE IF NOT EXISTS slot (
    id_meal INTEGER,
    id_plan INTEGER,
    meal_type TEXT CHECK (meal_type IN ('breakfast', 'lunch', 'dinner')),
    PRIMARY KEY (id_meal, meal_type),
    CONSTRAINT fk_meal_slot
       FOREIGN KEY (id_meal) REFERENCES meal(id)
       ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_plan_slot
       FOREIGN KEY (id_plan) REFERENCES plan(id)
       ON DELETE CASCADE ON UPDATE CASCADE
);