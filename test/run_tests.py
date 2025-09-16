import subprocess

def run_calc(input_data: str) -> str:
    """Executa o programa calc e retorna a saída como string."""
    process = subprocess.run(
        ["../calc"], input=input_data.encode(),
        stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    return process.stdout.decode()

def main():
    # Casos de teste: entrada -> saída esperada (parte relevante)
    tests = {
        # Operações válidas
        "2 + 3\n": "= 5",
        "7 - 4\n": "= 3",
        "6 * 7\n": "= 42",
        "20 / 5\n": "= 4",
        "10 % 3\n": "= 1",
        "(2 + 3) * 4\n": "= 20",
        "++5\n": "= 6",
        "5--\n": "= 4",

        # Erros
        "10 / 0\n": "Erro: divisão por zero",
        "10 % 0\n": "Erro: resto por zero",
        "foo + 2\n": "Erro: caractere inválido",
        "(2 + 3\n": "Erro de sintaxe",       # parêntese aberto
        "5 +\n": "Erro de sintaxe",          # operador sem operando
        "++\n": "Erro de sintaxe",           # operador isolado
        "--\n": "Erro de sintaxe",           # idem
        "exit\n": "Saindo..."
    }


    for expr, expected in tests.items():
        output = run_calc(expr)
        if expected in output:
            print(f"✅ {expr.strip()} -> OK ({expected})")
        else:
            print(f"❌ {expr.strip()} -> Falhou")

if __name__ == "__main__":
    main()
