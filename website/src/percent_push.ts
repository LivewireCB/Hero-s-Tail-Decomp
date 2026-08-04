export type Contributor = {
  github_username: string;
};

export type PercentPush = {
  milestone: number;
  date_reached?: Date;
  bg_color: string;
  text_color: string;
  contributors: Contributor[];
};

export const PERCENT_PUSHES: PercentPush[] = [
  {
    milestone: 10,
    bg_color: "gray",
    text_color: "black",
    // date_reached: new Date(2026, 0, 1),
    contributors: [],
  },
  {
    milestone: 25,
    bg_color: "gray",
    text_color: "black",
    contributors: [],
  },
  {
    milestone: 50,
    bg_color: "gray",
    text_color: "black",
    contributors: [],
  },
  {
    milestone: 75,
    bg_color: "gray",
    text_color: "black",
    contributors: [],
  },
];
