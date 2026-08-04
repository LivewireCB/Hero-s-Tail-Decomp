import { CodeHighlight } from "@mantine/code-highlight";
import { Anchor, Container, Group, Stack } from "@mantine/core";
import cppFunction from "./code/cpp.txt?raw";
import asmFunction from "./code/asm.txt?raw";
import "./css/about.css";

export function About() {
  return (
    <Container id="main" size={"lg"}>
      <Stack>
        <div>
          <h1>Spyro: A Hero's Tail Decompilation Project</h1>
          <div>
            <p>
              An effort to reverse engineer the 2004 game "
              <Anchor
                href="https://en.wikipedia.org/wiki/Spyro:_A_Hero%27s_Tail"
                target={"_blank"}
              >
                Spyro: A Hero's Tail
              </Anchor>
              ". This project aims to decompile the game's original binary code
              back into its source code form, targeting both the GameCube and
              PS2 versions of the game.
            </p>
            <p>
              The decompilation process involves analysing the compiled binary,
              reconstructing the original C++ source code, and verifying it
              compiles to a byte-for-byte identical binary.
            </p>
            <p>
              Source code is available on{" "}
              <Anchor
                href="https://github.com/LivewireCB/Hero-s-Tail-Decomp"
                target={"_blank"}
              >
                GitHub
              </Anchor>
              .
            </p>
          </div>
        </div>
        <Stack>
          <Group grow>
            <div>
              <h2>1. Assembly</h2>
              <CodeHighlight
                code={asmFunction}
                language={"x86asm"}
                withCopyButton={false}
                style={{ maxHeight: "300px", overflow: "auto" }}
              />
            </div>
            <div>
              <h2>2. C++ Source Code</h2>
              <CodeHighlight
                code={cppFunction}
                language={"cpp"}
                withCopyButton={false}
                style={{ maxHeight: "300px", overflow: "auto" }}
              />
            </div>
          </Group>
        </Stack>
      </Stack>
    </Container>
  );
}
