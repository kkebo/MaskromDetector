//
//  ContentView.swift
//  MyFirstDriverApp
//
//  Created by Kenta Kubo on 4/17/23.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        Button("Install dext") {
            UIApplication.shared.open(URL(string: UIApplication.openSettingsURLString)!)
        }
        .buttonStyle(.borderedProminent)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
