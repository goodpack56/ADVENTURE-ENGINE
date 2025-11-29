#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <conio.h>

// Export functions for Python to call
extern "C" {
    // Initialize random seed
    __declspec(dllexport) void init_engine() {
        srand(time(nullptr));
    }
    
    // Player stats
    __declspec(dllexport) int player_health = 100;
    __declspec(dllexport) int player_max_health = 100;
    __declspec(dllexport) int player_attack = 15;
    __declspec(dllexport) int player_defense = 0;
    __declspec(dllexport) int player_gold = 0;
    __declspec(dllexport) int player_mana = 50;
    __declspec(dllexport) int player_max_mana = 50;
    __declspec(dllexport) int player_level = 1;
    __declspec(dllexport) int player_xp = 0;
    __declspec(dllexport) int xp_to_next_level = 100;
    
    // Enemy stats
    __declspec(dllexport) int enemy_health = 50;
    __declspec(dllexport) int enemy_max_health = 50;
    __declspec(dllexport) int enemy_attack = rand() % 5 + 8;;
    __declspec(dllexport) int enemy_defense = 3;
    
    // Health management
    __declspec(dllexport) void player_take_damage(int damage) {
        int actual_damage = damage - player_defense;
        if (actual_damage < 0) actual_damage = 0;
        player_health -= actual_damage;
        if (player_health < 0) player_health = 0;
    }
    
    __declspec(dllexport) void player_heal(int amount) {
        player_health += amount;
        if (player_health > player_max_health) player_health = player_max_health;
    }
    
    __declspec(dllexport) int get_player_health() {
        return player_health;
    }
    
    __declspec(dllexport) bool is_player_alive() {
        return player_health > 0;
    }
    
    // Combat system
    __declspec(dllexport) int calculate_damage(int attack, int defense) {
        // Add some randomness (80% to 120% of base damage)
        int base_damage = attack - defense;
        if (base_damage < 1) base_damage = 1;
        
        int variance = (rand() % 40) - 20; // -20 to +20
        int final_damage = base_damage + (base_damage * variance / 100);
        
        if (final_damage < 1) final_damage = 1;
        return final_damage;
    }
    
    __declspec(dllexport) int player_attack_enemy() {
        int damage = calculate_damage(player_attack, enemy_defense);
        enemy_health -= damage;
        if (enemy_health < 0) enemy_health = 0;
        return damage;
    }
    
    __declspec(dllexport) int enemy_attack_player() {
        int damage = calculate_damage(enemy_attack, player_defense);
        player_health -= damage;
        if (player_health < 0) player_health = 0;
        return damage;
    }
    
    __declspec(dllexport) bool is_enemy_alive() {
        return enemy_health > 0;
    }
    
    __declspec(dllexport) int get_enemy_health() {
        return enemy_health;
    }
    
    // Create new enemy
    __declspec(dllexport) void spawn_enemy(int health, int attack, int defense) {
        enemy_max_health = health;
        enemy_health = health;
        enemy_attack = attack;
        enemy_defense = defense;
    }
    
    // Reward system
    __declspec(dllexport) void give_gold(int amount) {
        player_gold += amount;
    }
    
    __declspec(dllexport) int get_gold() {
        return player_gold;
    }
    
    // QTE - Get keypress without Enter
    __declspec(dllexport) char wait_for_keypress() {
        #ifdef _WIN32
            return _getch();
        #else
            return getchar();
        #endif
    }

    // Mana system
    __declspec(dllexport) void player_use_mana(int amount) {
        player_mana -= amount;
        if (player_mana < 0) player_mana = 0;
    }

    __declspec(dllexport) void restore_mana(int amount) {
        player_mana += amount;
        if (player_mana > player_max_mana) player_mana = player_max_mana;
    }

    __declspec(dllexport) int get_mana() {
        return player_mana;
    }

    __declspec(dllexport) bool has_mana(int amount) {
        return player_mana >= amount;
    }

    //leveling system
    __declspec(dllexport) void gain_xp(int amount) {
        player_xp += amount;

        //check for level up
        while (player_xp >= xp_to_next_level) {
            player_xp -= xp_to_next_level;
            player_level++;

            //increase stats on level up
            player_max_health += 10;
            player_health = player_max_health;
            player_attack += 2;
            player_defense += 2;

            //increase xp needed for next level
            xp_to_next_level = 100 + (player_level * 50);
        }
    }
    
    // show current level and xp
    __declspec(dllexport) int get_level() {
        return player_level;
    }

    __declspec(dllexport) int get_xp() {
        return player_xp;
    }

    // Critical hit system
    __declspec(dllexport) int player_crit_chance = 10;

    __declspec(dllexport) bool roll_crit() {
        int roll = rand() % 100;
        return roll < player_crit_chance;
    }

    __declspec(dllexport) int player_attack_enemy_crit(int base_attack) {
        int damage = calculate_damage(base_attack, enemy_defense);

        if (roll_crit()) {
            damage = damage * 2;
        }

        enemy_health -= damage;
        if (enemy_health < 0) enemy_health = 0;
        return damage;
    }

    // Inventory System
    __declspec(dllexport) int potion_count = 0;
    __declspec(dllexport) int weapon_tier = 0;
    __declspec(dllexport) int armor_tier = 0;

    __declspec(dllexport) void use_potion() {
        if (potion_count > 0) {
            potion_count--;
            player_heal(30);
        }
    }

    __declspec(dllexport) void equip_weapon(int tier) {
        weapon_tier = tier;
        player_attack = 15 + (tier * 5);
    }

    __declspec(dllexport) void equip_armor(int tier) {
        armor_tier = tier;
        player_defense = 5 + (tier * 3);
    }
}