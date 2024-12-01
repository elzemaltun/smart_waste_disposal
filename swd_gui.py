import customtkinter
import tkinter
import tkinter.messagebox

customtkinter.set_appearance_mode("System")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"


class Gui(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        # configure window
        self.title("Smart Waste Disposal Operational Board")
        self.geometry("700x450") 

        # configure grid layout (4x4)
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(1, weight=1)

        # navigation menu
        self.navigation_frame = customtkinter.CTkFrame(self, corner_radius=0)
        self.navigation_frame.grid(row=0, column=0, sticky="nsew")
        self.navigation_frame.grid_rowconfigure(4, weight=1)

        self.waste_level_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Waste Level",
                                                   fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                    anchor="w", command=self.waste_level_button_event)
        self.waste_level_button.grid(row=1, column=0, sticky="ew")

        self.temperature_level_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Temperature Level",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                       anchor="w", command=self.temperature_level_button_event)
        self.temperature_level_button.grid(row=2, column=0, sticky="ew")

        self.history_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="History",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                      anchor="w", command=self.history_button_event)
        self.history_button.grid(row=3, column=0, sticky="ew")

        # create home frame
        self.home_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.home_frame.grid_columnconfigure(0, weight=1)

        self.home_frame_label = customtkinter.CTkLabel(self.home_frame, text="")
        self.home_frame_label.grid(row=0, column=0, padx=20, pady=10)
        
        self.home_frame_button_1 = customtkinter.CTkButton(self.home_frame, text="EMPTY WASTE", fg_color="transparent", border_width=2, text_color=("gray10", "#DCE4EE"))
        self.home_frame_button_1.grid(row=3, column=0, padx=20, pady=10)
        
        # create second frame
        self.second_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.second_frame.grid_columnconfigure(0, weight=1)
        self.second_frame_label = customtkinter.CTkLabel(self.second_frame, text="")
        self.second_frame_label.grid(row=0, column=0, padx=20, pady=10)
        self.second_frame_button_1 = customtkinter.CTkButton(self.second_frame, text="FIX TEMP", fg_color="transparent", border_width=2, text_color=("gray10", "#DCE4EE"))
        self.second_frame_button_1.grid(row=1, column=0, padx=20, pady=10)

        # create third frame
        self.third_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")

        # select default frame
        self.select_frame_by_name("Waste Level")

    def select_frame_by_name(self, name):
        # set button color for selected button
        self.waste_level_button.configure(fg_color=("gray75", "gray25") if name == "Waste Level" else "transparent")
        self.temperature_level_button.configure(fg_color=("gray75", "gray25") if name == "Temperature Level" else "transparent")
        self.history_button.configure(fg_color=("gray75", "gray25") if name == "History" else "transparent")

        # show selected frame
        if name == "Waste Level":
            self.home_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.home_frame.grid_forget()
        if name == "Temperature Level":
            self.second_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.second_frame.grid_forget()
        if name == "History":
            self.third_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.third_frame.grid_forget()

    def waste_level_button_event(self):
        self.select_frame_by_name("Waste Level")

    def temperature_level_button_event(self):
        self.select_frame_by_name("Temperature Level")

    def history_button_event(self):
        self.select_frame_by_name("History")



root = Gui()
root.mainloop()