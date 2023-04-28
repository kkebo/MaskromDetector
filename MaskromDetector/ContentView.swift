//
//  ContentView.swift
//  MaskromDetector
//
//  Created by Kenta Kubo on 4/17/23.
//

import SwiftUI

struct ContentView: View {
    @State private var isMaskromMode: Bool?

    private var backgroundColor: Color {
        switch self.isMaskromMode {
        case .none: return .clear
        case .some(true): return .green.opacity(0.3)
        case .some(false): return .red.opacity(0.3)
        }
    }

    var body: some View {
        VStack(spacing: 20) {
            switch self.isMaskromMode {
            case .none:
                Image(systemName: "questionmark.circle")
                    .resizable()
                    .frame(width: 100, height: 100)
                Text(#"Please install dext first, connect your PinePhone Pro to this device, and tap "Test my PPP"."#)
                    .font(.title)
            case .some(true):
                Image(systemName: "checkmark.circle")
                    .resizable()
                    .frame(width: 100, height: 100)
                    .foregroundColor(.green)
                Text("Your PinePhone Pro is now in Maskrom mode.")
                    .font(.title)
                VStack {
                    Text("VID: 2207")
                    Text("PID: 330c")
                }
            case .some(false):
                Image(systemName: "xmark.circle")
                    .resizable()
                    .frame(width: 100, height: 100)
                    .foregroundColor(.red)
                Text("Your PinePhone Pro is not in Maskrom mode or is not connected to this device.")
                    .font(.title)
            }
            Button("Install dext") {
                UIApplication.shared.open(URL(string: UIApplication.openSettingsURLString)!)
            }
            .buttonStyle(.borderedProminent)
            .controlSize(.large)
            .hoverEffect()
            Button("Test my PPP") {
                self.isMaskromMode = IOServiceGetMatchingService(kIOMainPortDefault, IOServiceNameMatching("MaskromDriver")) != IO_OBJECT_NULL
            }
            .buttonStyle(.borderedProminent)
            .controlSize(.large)
            .hoverEffect()
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .background(self.backgroundColor)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
