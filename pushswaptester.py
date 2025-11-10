#!/usr/bin/env python3
import subprocess
import itertools
import random
import sys
from datetime import datetime

# ANSI color codes
GREEN = '\033[92m'
RED = '\033[91m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
RESET = '\033[0m'

class PushSwapTester:
    def __init__(self, program_path="./push_swap"):
        self.program_path = program_path
        self.log_file = f"push_swap_test_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"
        self.results = []
        
    def log(self, message, console=True):
        """Write to both console and log file"""
        if console:
            print(message)
        with open(self.log_file, 'a') as f:
            # Remove ANSI codes for log file
            clean_message = message
            for code in [GREEN, RED, YELLOW, BLUE, RESET]:
                clean_message = clean_message.replace(code, '')
            f.write(clean_message + '\n')
    
    def run_push_swap(self, numbers_str, expect_error=False):
        """Run push_swap and return (success, command_count, output, is_error)"""
        try:
            result = subprocess.run(
                [self.program_path, numbers_str],
                capture_output=True,
                text=True,
                timeout=5
            )
            
            # Check if output is exactly "Error\n"
            if result.stdout == "Error\n":
                return False, 0, "Error\n", True
            
            # If we expected an error but didn't get the right format
            if expect_error and result.stdout != "Error\n":
                return False, -1, f"Expected 'Error\\n' but got: '{result.stdout}'", False
            
            if result.returncode != 0:
                return False, -1, result.stderr, False
            
            # Count non-empty lines (each command)
            commands = [line for line in result.stdout.strip().split('\n') if line]
            return True, len(commands), result.stdout, False
            
        except subprocess.TimeoutExpired:
            return False, -1, "TIMEOUT", False
        except Exception as e:
            return False, -1, str(e), False
    
    def test_error_cases(self):
        """Test various error inputs"""
        self.log(f"\n{BLUE}{'='*60}")
        self.log("TESTING ERROR CASES")
        self.log(f"{'='*60}{RESET}\n")
        
        error_cases = [
            ("Duplicate numbers", "1 2 3 2 5"),
            ("Duplicate numbers (negative)", "-5 3 -5 7"),
            ("Invalid: leading plus with digits", "+45 67 89"),
            ("Invalid: double minus", "--6 7 8"),
            ("Invalid: trailing character", "67) 45 23"),
            ("Invalid: text", "some_text 45 67"),
            ("Invalid: mixed text and numbers", "12 34text 56"),
            ("Out of int bounds (positive)", "2147483648 1 2"),
            ("Out of int bounds (negative)", "-2147483649 1 2"),
            ("Invalid: empty string", ""),
            ("Invalid: only spaces", "   "),
            ("Invalid: decimal number", "3.14 5 7"),
            ("Invalid: leading zeros", "01 02 03"),
            ("Invalid: plus sign alone", "+ 5 7"),
            ("Invalid: minus sign alone", "- 5 7"),
            ("Invalid: multiple signs", "+-5 7 9"),
            ("Invalid: special characters", "5 @ 7"),
        ]
        
        passed = 0
        for desc, test_input in error_cases:
            success, count, output, is_error = self.run_push_swap(test_input, expect_error=True)
            if is_error and output == "Error\n":
                self.log(f"{GREEN}✓ {desc}: Correctly returned 'Error\\n'{RESET}")
                self.log(f"  Input: '{test_input}'")
                passed += 1
            elif not success and "Expected 'Error\\n'" in output:
                self.log(f"{RED}✗ {desc}: Wrong error format{RESET}")
                self.log(f"  Input: '{test_input}'")
                self.log(f"  {output}")
            else:
                self.log(f"{RED}✗ {desc}: Should have failed but didn't{RESET}")
                self.log(f"  Input: '{test_input}'")
                self.log(f"  Got {count} commands")
            self.log("")
        
        self.log(f"Error cases: {passed}/{len(error_cases)} passed\n")
        return passed == len(error_cases)
    
    def test_specific_size(self, size, test_name, numbers_list):
        """Test a specific list and log results"""
        numbers_str = ' '.join(map(str, numbers_list))
        success, count, output, is_error = self.run_push_swap(numbers_str, expect_error=False)
        
        if success:
            self.results.append({
                'size': size,
                'test': test_name,
                'count': count,
                'numbers': numbers_str
            })
            return True, count
        else:
            self.log(f"{RED}✗ Failed: {test_name}{RESET}")
            self.log(f"  Error: {output}")
            return False, -1
    
    def test_size_2(self):
        """Test all permutations of 2 elements"""
        self.log(f"\n{BLUE}{'='*60}")
        self.log("TESTING SIZE 2 (All permutations)")
        self.log(f"{'='*60}{RESET}\n")
        
        base = [1, 2]
        perms = list(itertools.permutations(base))
        
        for perm in perms:
            test_name = f"Perm: {perm}"
            success, count = self.test_specific_size(2, test_name, list(perm))
            if success:
                self.log(f"  {perm} → {count} commands")
        
        self.log(f"\nCompleted {len(perms)} permutations of size 2\n")
    
    def test_size_3(self):
        """Test all permutations of 3 elements"""
        self.log(f"\n{BLUE}{'='*60}")
        self.log("TESTING SIZE 3 (All permutations)")
        self.log(f"{'='*60}{RESET}\n")
        
        base = [1, 2, 3]
        perms = list(itertools.permutations(base))
        
        max_commands = 0
        for perm in perms:
            test_name = f"Perm: {perm}"
            success, count = self.test_specific_size(3, test_name, list(perm))
            if success:
                max_commands = max(max_commands, count)
                self.log(f"  {perm} → {count} commands")
        
        self.log(f"\nCompleted {len(perms)} permutations of size 3")
        self.log(f"Maximum commands used: {max_commands}\n")
    
    def test_size_5(self):
        """Test all permutations of 5 elements"""
        self.log(f"\n{BLUE}{'='*60}")
        self.log("TESTING SIZE 5 (All permutations)")
        self.log(f"{'='*60}{RESET}\n")
        
        base = [1, 2, 3, 4, 5]
        perms = list(itertools.permutations(base))
        
        max_commands = 0
        total = len(perms)
        
        self.log(f"Testing {total} permutations...\n")
        
        for i, perm in enumerate(perms, 1):
            test_name = f"Perm {i}/{total}"
            success, count = self.test_specific_size(5, test_name, list(perm))
            if success:
                max_commands = max(max_commands, count)
                if i % 24 == 0:  # Progress update every 24 permutations
                    self.log(f"Progress: {i}/{total} - Max commands so far: {max_commands}")
        
        self.log(f"\nCompleted {total} permutations of size 5")
        self.log(f"Maximum commands used: {max_commands}\n")
    
    def generate_random_list(self, size):
        """Generate random unique integers"""
        # Use a range larger than size to ensure variety
        range_size = size * 10
        numbers = random.sample(range(-range_size, range_size), size)
        return numbers
    
    def get_rating(self, size, commands):
        """Get performance rating based on size and command count"""
        if size == 100:
            if commands > 1300:
                return "FAIL", RED
            elif commands < 700:
                return "GREAT", GREEN
            elif commands < 1100:
                return "DECENT", YELLOW
            else:
                return "AVERAGE", YELLOW
        elif size == 500:
            if commands > 11500:
                return "FAIL", RED
            elif commands < 5500:
                return "GREAT", GREEN
            elif commands < 8500:
                return "DECENT", YELLOW
            else:
                return "AVERAGE", YELLOW
        return None, RESET
    
    def test_size_range(self, size, num_tests):
        """Test a specific size with multiple random cases and edge cases"""
        self.log(f"\n{BLUE}{'='*60}")
        self.log(f"TESTING SIZE {size}")
        self.log(f"{'='*60}{RESET}\n")
        
        all_counts = []
        ratings_count = {"FAIL": 0, "AVERAGE": 0, "DECENT": 0, "GREAT": 0}
        
        # Edge cases
        edge_cases = [
            ("Already sorted", list(range(1, size + 1))),
            ("Reverse sorted", list(range(size, 0, -1))),
            ("Negative numbers sorted", list(range(-size, 0))),
            ("Negative numbers reverse", list(range(-1, -size - 1, -1))),
            ("Mixed pos/neg sorted", list(range(-size//2, size//2 + 1))),
            ("All negative", random.sample(range(-size*2, -1), size)),
            ("Large numbers", random.sample(range(1000000, 2000000), size)),
            ("Near INT_MAX", random.sample(range(2147483647 - size*2, 2147483647), size)),
            ("Near INT_MIN", random.sample(range(-2147483648, -2147483648 + size*2), size)),
        ]
        
        self.log("Edge cases:")
        for desc, nums in edge_cases:
            success, count = self.test_specific_size(size, desc, nums)
            if success:
                all_counts.append(count)
                rating, color = self.get_rating(size, count)
                if rating:
                    ratings_count[rating] += 1
                    self.log(f"  {desc}: {count} commands {color}[{rating}]{RESET}")
                else:
                    self.log(f"  {desc}: {count} commands")
        
        self.log(f"\nRandom test cases (0/{num_tests})...")
        
        # Random cases
        for i in range(num_tests):
            nums = self.generate_random_list(size)
            success, count = self.test_specific_size(size, f"Random {i+1}", nums)
            if success:
                all_counts.append(count)
                rating, _ = self.get_rating(size, count)
                if rating:
                    ratings_count[rating] += 1
                if (i + 1) % 10 == 0:
                    self.log(f"Progress: {i+1}/{num_tests} - Avg: {sum(all_counts)/len(all_counts):.1f}, Max: {max(all_counts)}")
        
        # Statistics
        if all_counts:
            avg = sum(all_counts) / len(all_counts)
            maximum = max(all_counts)
            minimum = min(all_counts)
            
            self.log(f"\n{YELLOW}Statistics for size {size}:{RESET}")
            self.log(f"  Tests run: {len(all_counts)}")
            self.log(f"  Average commands: {avg:.2f}")
            self.log(f"  Minimum commands: {minimum}")
            self.log(f"  Maximum commands: {maximum}")
            
            # Display ratings distribution for sizes 100 and 500
            if size in [100, 500]:
                self.log(f"\n  Performance breakdown:")
                if ratings_count["FAIL"] > 0:
                    self.log(f"    {RED}FAIL{RESET}: {ratings_count['FAIL']} tests")
                if ratings_count["AVERAGE"] > 0:
                    self.log(f"    {YELLOW}AVERAGE{RESET}: {ratings_count['AVERAGE']} tests")
                if ratings_count["DECENT"] > 0:
                    self.log(f"    {YELLOW}DECENT{RESET}: {ratings_count['DECENT']} tests")
                if ratings_count["GREAT"] > 0:
                    self.log(f"    {GREEN}GREAT{RESET}: {ratings_count['GREAT']} tests")
                
                # Overall assessment
                avg_rating, avg_color = self.get_rating(size, int(avg))
                self.log(f"\n  Overall rating based on average: {avg_color}{avg_rating}{RESET}")
            
            self.log("")
    
    def generate_summary(self):
        """Generate summary statistics"""
        self.log(f"\n{BLUE}{'='*60}")
        self.log("SUMMARY")
        self.log(f"{'='*60}{RESET}\n")
        
        if not self.results:
            self.log("No results to summarize")
            return
        
        # Group by size
        by_size = {}
        for result in self.results:
            size = result['size']
            if size not in by_size:
                by_size[size] = []
            by_size[size].append(result['count'])
        
        for size in sorted(by_size.keys()):
            counts = by_size[size]
            avg = sum(counts) / len(counts)
            self.log(f"Size {size:3d}: {len(counts):4d} tests, "
                    f"Avg: {avg:6.2f}, Max: {max(counts):4d}, Min: {min(counts):4d}")
        
        self.log(f"\nResults saved to: {self.log_file}")
    
    def run_all_tests(self):
        """Run complete test suite"""
        self.log(f"{BLUE}{'='*60}")
        self.log("PUSH_SWAP TESTER")
        self.log(f"{'='*60}{RESET}")
        self.log(f"Program: {self.program_path}")
        self.log(f"Log file: {self.log_file}")
        self.log(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        
        # Test error cases
        self.test_error_cases()
        
        # Test size 2
        self.test_size_2()
        
        # Test size 3 (all permutations)
        self.test_size_3()
        
        # Test size 5 (all permutations)
        self.test_size_5()
        
        # Test size 49 (100 random tests)
        self.test_size_range(49, num_tests=100)
        
        # Test size 100 (100 random tests)
        self.test_size_range(100, num_tests=100)
        
        # Test size 500 (50 random tests - fewer because it's slower)
        self.test_size_range(500, num_tests=50)
        
        # Generate summary
        self.generate_summary()

def main():
    if len(sys.argv) > 1:
        program_path = sys.argv[1]
    else:
        program_path = "./push_swap"
    
    print(f"{YELLOW}Push_swap Comprehensive Tester{RESET}")
    print(f"Using program: {program_path}\n")
    
    tester = PushSwapTester(program_path)
    tester.run_all_tests()

if __name__ == "__main__":
    main()
