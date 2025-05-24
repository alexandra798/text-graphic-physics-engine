#!/usr/bin/env python3
import os
import re
from collections import defaultdict
from typing import Dict, Set, List, Tuple

class MakefileAnalyzer:
    def __init__(self, directory: str):
        self.directory = directory
        self.dependencies: Dict[str, Set[str]] = defaultdict(set)
        self.source_files: Set[str] = set()
        self.header_files: Set[str] = set()
        self.existing_rules: Dict[str, Set[str]] = defaultdict(set)
        # Standard library headers that should not be included in dependencies
        self.std_headers = {
            'iostream.h', 'cmath.h', 'vector.h', 'initializer_list.h',
            'stdexcept.h', 'memory.h', 'iomanip.h', 'string.h', 'algorithm.h',
            'cstdlib.h', 'cstring.h', 'cstdio.h', 'ctime.h', 'cassert.h',
            'fstream.h', 'sstream.h', 'map.h', 'set.h', 'list.h', 'queue.h',
            'stack.h', 'deque.h', 'unordered_map.h', 'unordered_set.h',
            'functional.h', 'numeric.h', 'random.h', 'chrono.h', 'thread.h',
            'mutex.h', 'condition_variable.h', 'future.h', 'atomic.h',
            'array.h', 'tuple.h', 'utility.h', 'type_traits.h', 'limits.h',
            'cstdint.h', 'cfloat.h', 'climits.h', 'cstddef.h', 'cstdarg.h',
            'cctype.h', 'cwctype.h', 'cstdbool.h', 'cstdalign.h', 'cstdnoreturn.h'
        }
        
    def find_source_files(self):
        """Find all .cc and .h files in the directory."""
        for file in os.listdir(self.directory):
            if file.endswith('.cc'):
                self.source_files.add(file)
            elif file.endswith('.h'):
                self.header_files.add(file)
    
    def parse_includes(self, file_path: str) -> Set[str]:
        """Parse #include statements in a file."""
        includes = set()
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                # Match both #include <...> and #include "..."
                matches = re.finditer(r'#include\s*[<"]([^>"]+)[>"]', content)
                for match in matches:
                    include_file = match.group(1)
                    # Handle both with and without .h extension
                    if not include_file.endswith('.h'):
                        include_file += '.h'
                    # Only add non-standard library headers
                    if include_file not in self.std_headers:
                        includes.add(include_file)
        except Exception as e:
            print(f"Error reading {file_path}: {e}")
        return includes
    
    def build_dependency_graph(self):
        """Build dependency graph for all source files."""
        for source_file in self.source_files:
            file_path = os.path.join(self.directory, source_file)
            includes = self.parse_includes(file_path)
            self.dependencies[source_file] = includes
            
            # Also check the corresponding header file if it exists
            header_file = source_file[:-3] + '.h'
            if header_file in self.header_files:
                header_path = os.path.join(self.directory, header_file)
                header_includes = self.parse_includes(header_path)
                self.dependencies[source_file].update(header_includes)
    
    def parse_existing_makefile(self):
        """Parse existing Makefile to get current rules."""
        makefile_path = os.path.join(self.directory, 'Makefile')
        try:
            with open(makefile_path, 'r', encoding='utf-8') as f:
                content = f.read()
                # Match target: dependencies pattern
                for line in content.split('\n'):
                    if ':' in line and not line.startswith('\t'):
                        parts = line.split(':')
                        if len(parts) >= 2:
                            target = parts[0].strip()
                            deps = set(d.strip() for d in parts[1].split() if d.strip())
                            self.existing_rules[target] = deps
        except Exception as e:
            print(f"Error reading Makefile: {e}")
    
    def generate_makefile_rules(self) -> str:
        """Generate Makefile rules based on dependencies."""
        rules = []
        
        # Add compiler settings
        rules.extend([
            "CC = $(CXX)",
            "CXXFLAGS = -std=c++17",
            "CXXFLAGS += -pedantic -Wall -Wextra -Werror",
            "CXXFLAGS += -g",
            "",
            ".PHONY: all clean",
            "",
            "all: testVecteur testIntegrateur1 testPointMateriel",
            ""
        ])
        
        # Generate object file rules
        for source_file in self.source_files:
            obj_file = source_file[:-3] + '.o'
            deps = self.dependencies[source_file]
            deps.add(source_file)  # Add the source file itself as dependency
            
            # Add corresponding header if it exists
            header_file = source_file[:-3] + '.h'
            if header_file in self.header_files:
                deps.add(header_file)
            
            rule = f"{obj_file}: {' '.join(sorted(deps))}"
            rules.append(rule)
            rules.append(f"\t$(CXX) $(CXXFLAGS) -c {source_file}")
            rules.append("")
        
        # Generate executable rules
        executables = {
            'testVecteur': ['testVecteur.o', 'Vecteur.o'],
            'testIntegrateur1': [
                'testIntegrateur1.o', 'PointMateriel.o', 'Vecteur.o',
                'ObjetMobile.o', 'ObjetPhysique.o', 'GravitationConstante.o',
                'IntegrateurEulerCromer.o', 'Libre.o'
            ],
            'testPointMateriel': [
                'testPointMateriel.o', 'PointMateriel.o', 'Libre.o',
                'Vecteur.o', 'ObjetMobile.o', 'ObjetPhysique.o',
                'GravitationConstante.o', 'IntegrateurEulerCromer.o',
                'TextViewer.o', 'Systeme.o', 'ChargeElectrique.o',
                'ChampNewtonien.o', 'ForceCentrale.o'
            ]
        }
        
        for exe, deps in executables.items():
            rules.append(f"{exe}: {' '.join(deps)}")
            rules.append(f"\t$(CXX) -o {exe} {' '.join(deps)}")
            rules.append("")
        
        # Add clean rule
        rules.extend([
            "clean:",
            "\trm -f *.o testVecteur testIntegrateur1 testPointMateriel",
            ""
        ])
        
        return '\n'.join(rules)
    
    def analyze_makefile(self) -> Tuple[bool, List[str]]:
        """Analyze existing Makefile for missing or incorrect rules."""
        issues = []
        
        # Check if all source files have corresponding object rules
        for source_file in self.source_files:
            obj_file = source_file[:-3] + '.o'
            if obj_file not in self.existing_rules:
                issues.append(f"Missing rule for {obj_file}")
        
        # Check if all executables are properly defined
        executables = ['testVecteur', 'testIntegrateur1', 'testPointMateriel']
        for exe in executables:
            if exe not in self.existing_rules:
                issues.append(f"Missing rule for executable {exe}")
        
        # Check dependencies in existing rules
        for target, deps in self.existing_rules.items():
            if target.endswith('.o'):
                source_file = target[:-2] + '.cc'
                if source_file in self.source_files:
                    expected_deps = self.dependencies[source_file]
                    missing_deps = expected_deps - deps
                    if missing_deps:
                        issues.append(f"Missing dependencies for {target}: {missing_deps}")
        
        return len(issues) == 0, issues

def main():
    analyzer = MakefileAnalyzer('.')
    analyzer.find_source_files()
    analyzer.build_dependency_graph()
    analyzer.parse_existing_makefile()
    
    # Analyze existing Makefile
    is_valid, issues = analyzer.analyze_makefile()
    
    print("=== Makefile Analysis Report ===")
    if is_valid:
        print("✓ Current Makefile is valid")
    else:
        print("✗ Issues found in current Makefile:")
        for issue in issues:
            print(f"  - {issue}")
    
    print("\n=== Generated Makefile ===")
    print(analyzer.generate_makefile_rules())
    
    # Save the generated Makefile to a new file
    with open('Makefile.new', 'w', encoding='utf-8') as f:
        f.write(analyzer.generate_makefile_rules())
    print("\nGenerated Makefile has been saved to 'Makefile.new'")

if __name__ == '__main__':
    main() 